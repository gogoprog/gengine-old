#include "entity_component_spine.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "graphics_animation.h"
#include "entity_system.h"
#include "entity_entity.h"
#include "script.h"
#include "debug.h"
#include "entity.h"
#include <algorithm>
#include <string.h>

namespace gengine
{
namespace entity
{

ComponentSpine::ComponentSpine()
    :
    Component(),
    timeFactor(1.0f),
    worldIndex(0),
    size(2048)
{
}

ComponentSpine::~ComponentSpine()
{
    if(skeleton)
    {
        spSkeleton_dispose(skeleton);
        spAnimationState_dispose(animationState);
    }
}

void ComponentSpine::init()
{
    mesh.init(size, size * 2);
}

void ComponentSpine::insert()
{
    graphics::System::getInstance().getWorld(worldIndex).addObject(mesh);
}

void ComponentSpine::update(const float dt)
{
    if(!skeleton)
    {
        return;
    }

    Transform & transform = entity->transform;

    mesh.setPosition(transform.position);
    mesh.setRotation(transform.rotation);
    mesh.setScale(transform.scale);

    spSkeleton_update(skeleton, dt * timeFactor);
    spAnimationState_update(animationState, dt * timeFactor);
    spAnimationState_apply(animationState, skeleton);
    spSkeleton_updateWorldTransform(skeleton);

    auto vertices = mesh.getVertexBuffer().map();
    auto indices = mesh.getIndexBuffer().map();
    uint vertex_count = 0;
    uint index_count = 0;

    for(int i = 0; i < skeleton->slotsCount; ++i)
    {
        auto slot = skeleton->drawOrder[i];
        auto attachment = slot->attachment;

        if(!attachment)
        {
            continue;
        }

        switch(attachment->type)
        {
            case SP_ATTACHMENT_REGION:
            {
                Vector2 computed_vertices[4];
                auto region_attachment = (spRegionAttachment*)attachment;
                auto color = Vector4(
                    skeleton->r * slot->r,
                    skeleton->g * slot->g,
                    skeleton->b * slot->b,
                    skeleton->a * slot->a
                    );

                mesh.setTexture(* (graphics::Texture*)((spAtlasRegion*)region_attachment->rendererObject)->page->rendererObject);

                spRegionAttachment_computeWorldVertices(region_attachment, slot->bone, (float *)computed_vertices);

                vertices[vertex_count].color = color;
                vertices[vertex_count].position = computed_vertices[0];
                vertices[vertex_count].texCoords.x = region_attachment->uvs[SP_VERTEX_X1];
                vertices[vertex_count].texCoords.y = region_attachment->uvs[SP_VERTEX_Y1];

                vertices[vertex_count + 1].color = color;
                vertices[vertex_count + 1].position = computed_vertices[1];
                vertices[vertex_count + 1].texCoords.x = region_attachment->uvs[SP_VERTEX_X2];
                vertices[vertex_count + 1].texCoords.y = region_attachment->uvs[SP_VERTEX_Y2];

                vertices[vertex_count + 2].color = color;
                vertices[vertex_count + 2].position = computed_vertices[2];
                vertices[vertex_count + 2].texCoords.x = region_attachment->uvs[SP_VERTEX_X3];
                vertices[vertex_count + 2].texCoords.y = region_attachment->uvs[SP_VERTEX_Y3];

                vertices[vertex_count + 3].color = color;
                vertices[vertex_count + 3].position = computed_vertices[3];
                vertices[vertex_count + 3].texCoords.x = region_attachment->uvs[SP_VERTEX_X4];
                vertices[vertex_count + 3].texCoords.y = region_attachment->uvs[SP_VERTEX_Y4];

                indices[index_count + 0] = vertex_count + 0;
                indices[index_count + 1] = vertex_count + 1;
                indices[index_count + 2] = vertex_count + 2;
                indices[index_count + 3] = vertex_count + 2;
                indices[index_count + 4] = vertex_count + 3;
                indices[index_count + 5] = vertex_count + 0;

                vertex_count += 4;
                index_count += 6;
            }
            break;

            case SP_ATTACHMENT_MESH:
            {
                auto sp_mesh = (spMeshAttachment*)attachment;
                auto initial_vertex_count = vertex_count;
                auto color = Vector4(
                    skeleton->r * slot->r,
                    skeleton->g * slot->g,
                    skeleton->b * slot->b,
                    skeleton->a * slot->a
                    );

                float *_vertices = sp_mesh->vertices;
                const spBone* bone = slot->bone;
                float x = bone->skeleton->x + bone->worldX, y = bone->skeleton->y + bone->worldY;

                mesh.setTexture(* (graphics::Texture*)((spAtlasRegion*)sp_mesh->rendererObject)->page->rendererObject);

                if(slot->attachmentVerticesCount == sp_mesh->verticesCount)
                {
                    _vertices = slot->attachmentVertices;
                }

                for(int i = 0; i < sp_mesh->verticesCount; i += 2)
                {
                    const float vx = _vertices[i], vy = _vertices[i + 1];
                    auto & vertex = vertices[initial_vertex_count + i / 2];
                    vertex.position.x = vx * bone->m00 + vy * bone->m01 + x;
                    vertex.position.y = vx * bone->m10 + vy * bone->m11 + y;
                    vertex.texCoords.u = sp_mesh->uvs[i];
                    vertex.texCoords.v = sp_mesh->uvs[i + 1];
                    vertex.color = color;
                    ++vertex_count;
                }

                for(int i = 0; i < sp_mesh->trianglesCount; ++i)
                {
                    int index = sp_mesh->triangles[i] << 1;
                    indices[index_count] = initial_vertex_count + index / 2;
                    ++index_count;
                }
            }
            break;

            case SP_ATTACHMENT_SKINNED_MESH:
            {
                auto sp_mesh = (spSkinnedMeshAttachment*)attachment;
                auto initial_vertex_count = vertex_count;
                auto color = Vector4(
                    skeleton->r * slot->r,
                    skeleton->g * slot->g,
                    skeleton->b * slot->b,
                    skeleton->a * slot->a
                    );

                mesh.setTexture(* (graphics::Texture*)((spAtlasRegion*)sp_mesh->rendererObject)->page->rendererObject);

                int w = 0, v = 0, b = 0, f = 0;
                float x = slot->bone->skeleton->x, y = slot->bone->skeleton->y;
                spBone** skeletonBones = slot->bone->skeleton->bones;

                if(slot->attachmentVerticesCount == 0)
                {
                    for(; v < sp_mesh->bonesCount; w += 2)
                    {
                        float wx = 0, wy = 0;
                        const int nn = sp_mesh->bones[v] + v;
                        v++;
                        for(; v <= nn; v++, b += 3)
                        {
                            const spBone* bone = skeletonBones[sp_mesh->bones[v]];
                            const float vx = sp_mesh->weights[b], vy = sp_mesh->weights[b + 1], weight = sp_mesh->weights[b + 2];
                            wx += (vx * bone->m00 + vy * bone->m01 + bone->worldX) * weight;
                            wy += (vx * bone->m10 + vy * bone->m11 + bone->worldY) * weight;
                        }
                        auto & vertex = vertices[initial_vertex_count + w / 2];
                        ++vertex_count;
                        vertex.position.x = wx + x;
                        vertex.position.y = wy + y;
                        vertex.texCoords.u = sp_mesh->uvs[w];
                        vertex.texCoords.v = sp_mesh->uvs[w + 1];
                        vertex.color = color;
                    }
                }
                else
                {
                    const float* ffd = slot->attachmentVertices;
                    for(; v < sp_mesh->bonesCount; w += 2)
                    {
                        float wx = 0, wy = 0;
                        const int nn = sp_mesh->bones[v] + v;
                        v++;
                        for(; v <= nn; v++, b += 3, f += 2)
                        {
                            const spBone* bone = skeletonBones[sp_mesh->bones[v]];
                            const float vx = sp_mesh->weights[b] + ffd[f], vy = sp_mesh->weights[b + 1] + ffd[f + 1], weight = sp_mesh->weights[b + 2];
                            wx += (vx * bone->m00 + vy * bone->m01 + bone->worldX) * weight;
                            wy += (vx * bone->m10 + vy * bone->m11 + bone->worldY) * weight;
                        }
                        auto & vertex = vertices[initial_vertex_count + w / 2];
                        ++vertex_count;
                        vertex.position.x = wx + x;
                        vertex.position.y = wy + y;
                        vertex.texCoords.u = sp_mesh->uvs[w];
                        vertex.texCoords.v = sp_mesh->uvs[w + 1];
                        vertex.color = color;
                    }
                }

                for(int i = 0; i < sp_mesh->trianglesCount; ++i)
                {
                    int index = sp_mesh->triangles[i] << 1;
                    indices[index_count] = initial_vertex_count + index / 2;
                    ++index_count;
                }
            }
            break;

            default:
            break;
        }
    }

    mesh.setVertexCount(vertex_count);
    mesh.setIndexCount(index_count);
    mesh.getVertexBuffer().unMap();
    mesh.getIndexBuffer().unMap();
}
void ComponentSpine::remove()
{
    graphics::System::getInstance().getWorld(worldIndex).removeObject(mesh);
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSpine)
{
    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        setAnimation,
        {
            SCRIPT_GET_SELF(ComponentSpine);
            auto animation = static_cast<const graphics::SpineManagerItem *>(lua_touserdata(state, 2));
            self.setAnimation(
                animation,
                static_cast<int>(lua_tonumber(state, 3)),
                lua_toboolean(state, 4)
                );
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        addAnimation,
        {
            SCRIPT_GET_SELF(ComponentSpine);
            auto animation = static_cast<const graphics::SpineManagerItem *>(lua_touserdata(state, 2));
            self.addAnimation(
                animation,
                static_cast<int>(lua_tonumber(state, 3)),
                lua_toboolean(state, 4),
                lua_tonumber(state, 5)
                );
            return 0;
        }
        );
}

ENTITY_COMPONENT_SETTERS(ComponentSpine)
{
    ENTITY_COMPONENT_SETTER_FIRST(animation)
    {
        auto animation = static_cast<const graphics::SpineManagerItem *>(lua_touserdata(state, 3));
        self.setAnimation(animation, 0, false);
    }
    ENTITY_COMPONENT_SETTER(layer)
    {
        self.mesh.setLayer(lua_tonumber(state, 3));
    }
    ENTITY_COMPONENT_SETTER(timeFactor)
    {
        self.timeFactor = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(color)
    {
        Vector4::fill(state, self.mesh.getColor(), 3);
    }
    ENTITY_COMPONENT_SETTER(alpha)
    {
        self.mesh.setColorAlpha(lua_tonumber(state, 3));
    }
    ENTITY_COMPONENT_SETTER(size)
    {
        self.size = static_cast<uint>(lua_tonumber(state, 3));
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

void ComponentSpine::setAnimation(const graphics::SpineManagerItem * _animation, const int track_index, const bool loop)
{
    auto __animation = * const_cast<graphics::SpineManagerItem *>(_animation);

    updateSpine(__animation);

    spAnimationState_setAnimation(animationState, track_index, __animation.getAnimation(), loop);
}

void ComponentSpine::addAnimation(const graphics::SpineManagerItem * _animation, const int track_index, const bool loop, const float delay)
{
    auto __animation = * const_cast<graphics::SpineManagerItem *>(_animation);

    updateSpine(__animation);

    spAnimationState_addAnimation(animationState, track_index, __animation.getAnimation(), loop, delay);
}

void ComponentSpine::updateSpine(graphics::SpineManagerItem & animation)
{
    if(skeleton && skeleton->data != animation.getSkeletonData())
    {
        spSkeleton_dispose(skeleton);
        spAnimationState_dispose(animationState);
        skeleton = nullptr;
    }

    if(!skeleton)
    {
        skeleton = spSkeleton_create(animation.getSkeletonData());
        animationState = spAnimationState_create(animation.getAnimationStateData());
    }
}

}
}
