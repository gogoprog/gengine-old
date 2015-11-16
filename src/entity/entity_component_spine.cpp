#include "entity_component_spine.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "graphics_animation.h"
#include "entity_system.h"
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
    timeFactor(1.0f),
    worldIndex(0)
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

ENTITY_COMPONENT_IMPLEMENT(ComponentSpine)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(setAnimation);
    ENTITY_COMPONENT_PUSH_FUNCTION(addAnimation);
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
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpine, init)
{
    self.mesh.init(1024, 1024);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpine, insert)
{
    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.mesh);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpine, update)
{
    if(!self.skeleton)
    {
        return 0;
    }

    auto dt = System::getInstance().getCurrentDt();
    auto & mesh = self.mesh;

    Transform transform;

    getTransformFromComponent(state, transform);

    mesh.setPosition(transform.position);
    mesh.setRotation(transform.rotation);
    mesh.setScale(transform.scale);

    spSkeleton_update(self.skeleton, dt * self.timeFactor);
    spAnimationState_update(self.animationState, dt * self.timeFactor);
    spAnimationState_apply(self.animationState, self.skeleton);
    spSkeleton_updateWorldTransform(self.skeleton);

    auto vertices = self.mesh.getVertexBuffer().map();
    auto indices = self.mesh.getIndexBuffer().map();
    uint vertex_count = 0;
    uint index_count = 0;

    for(int i = 0; i < self.skeleton->slotsCount; ++i)
    {
        auto slot = self.skeleton->drawOrder[i];
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
                    self.skeleton->r * slot->r,
                    self.skeleton->g * slot->g,
                    self.skeleton->b * slot->b,
                    self.skeleton->a * slot->a
                    );

                self.mesh.setTexture(* (graphics::Texture*)((spAtlasRegion*)region_attachment->rendererObject)->page->rendererObject);

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
                auto mesh = (spMeshAttachment*)attachment;
                auto initial_vertex_count = vertex_count;
                auto color = Vector4(
                    self.skeleton->r * slot->r,
                    self.skeleton->g * slot->g,
                    self.skeleton->b * slot->b,
                    self.skeleton->a * slot->a
                    );

                float *_vertices = mesh->vertices;
                const spBone* bone = slot->bone;
                float x = bone->skeleton->x + bone->worldX, y = bone->skeleton->y + bone->worldY;

                self.mesh.setTexture(* (graphics::Texture*)((spAtlasRegion*)mesh->rendererObject)->page->rendererObject);

                if(slot->attachmentVerticesCount == mesh->verticesCount)
                {
                    _vertices = slot->attachmentVertices;
                }

                for(int i = 0; i < mesh->verticesCount; i += 2)
                {
                    const float vx = _vertices[i], vy = _vertices[i + 1];
                    auto & vertex = vertices[initial_vertex_count + i / 2];
                    vertex.position.x = vx * bone->m00 + vy * bone->m01 + x;
                    vertex.position.y = vx * bone->m10 + vy * bone->m11 + y;
                    vertex.texCoords.u = mesh->uvs[i];
                    vertex.texCoords.v = mesh->uvs[i + 1];
                    vertex.color = color;
                    ++vertex_count;
                }

                for(int i = 0; i < mesh->trianglesCount; ++i)
                {
                    int index = mesh->triangles[i] << 1;
                    indices[index_count] = initial_vertex_count + index / 2;
                    ++index_count;
                }
            }
            break;

            case SP_ATTACHMENT_SKINNED_MESH:
            {
                auto mesh = (spSkinnedMeshAttachment*)attachment;
                auto initial_vertex_count = vertex_count;
                auto color = Vector4(
                    self.skeleton->r * slot->r,
                    self.skeleton->g * slot->g,
                    self.skeleton->b * slot->b,
                    self.skeleton->a * slot->a
                    );

                self.mesh.setTexture(* (graphics::Texture*)((spAtlasRegion*)mesh->rendererObject)->page->rendererObject);

                int w = 0, v = 0, b = 0, f = 0;
                float x = slot->bone->skeleton->x, y = slot->bone->skeleton->y;
                spBone** skeletonBones = slot->bone->skeleton->bones;

                if(slot->attachmentVerticesCount == 0)
                {
                    for(; v < mesh->bonesCount; w += 2)
                    {
                        float wx = 0, wy = 0;
                        const int nn = mesh->bones[v] + v;
                        v++;
                        for(; v <= nn; v++, b += 3)
                        {
                            const spBone* bone = skeletonBones[mesh->bones[v]];
                            const float vx = mesh->weights[b], vy = mesh->weights[b + 1], weight = mesh->weights[b + 2];
                            wx += (vx * bone->m00 + vy * bone->m01 + bone->worldX) * weight;
                            wy += (vx * bone->m10 + vy * bone->m11 + bone->worldY) * weight;
                        }
                        auto & vertex = vertices[initial_vertex_count + w / 2];
                        ++vertex_count;
                        vertex.position.x = wx + x;
                        vertex.position.y = wy + y;
                        vertex.texCoords.u = mesh->uvs[w];
                        vertex.texCoords.v = mesh->uvs[w + 1];
                        vertex.color = color;
                    }
                }
                else
                {
                    const float* ffd = slot->attachmentVertices;
                    for(; v < mesh->bonesCount; w += 2)
                    {
                        float wx = 0, wy = 0;
                        const int nn = mesh->bones[v] + v;
                        v++;
                        for(; v <= nn; v++, b += 3, f += 2)
                        {
                            const spBone* bone = skeletonBones[mesh->bones[v]];
                            const float vx = mesh->weights[b] + ffd[f], vy = mesh->weights[b + 1] + ffd[f + 1], weight = mesh->weights[b + 2];
                            wx += (vx * bone->m00 + vy * bone->m01 + bone->worldX) * weight;
                            wy += (vx * bone->m10 + vy * bone->m11 + bone->worldY) * weight;
                        }
                        auto & vertex = vertices[initial_vertex_count + w / 2];
                        ++vertex_count;
                        vertex.position.x = wx + x;
                        vertex.position.y = wy + y;
                        vertex.texCoords.u = mesh->uvs[w];
                        vertex.texCoords.v = mesh->uvs[w + 1];
                        vertex.color = color;
                    }
                }

                for(int i = 0; i < mesh->trianglesCount; ++i)
                {
                    int index = mesh->triangles[i] << 1;
                    indices[index_count] = initial_vertex_count + index / 2;
                    ++index_count;
                }
            }
            break;

            default:
            break;
        }
    }

    self.mesh.setVertexCount(vertex_count);
    self.mesh.setIndexCount(index_count);
    self.mesh.getVertexBuffer().unMap();
    self.mesh.getIndexBuffer().unMap();
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpine, remove)
{
    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.mesh);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpine, setAnimation)
{
    auto animation = static_cast<const graphics::SpineManagerItem *>(lua_touserdata(state, 2));
    self.setAnimation(
        animation,
        static_cast<int>(lua_tonumber(state, 3)),
        lua_toboolean(state, 4)
        );
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpine, addAnimation)
{
    auto animation = static_cast<const graphics::SpineManagerItem *>(lua_touserdata(state, 2));
    self.addAnimation(
        animation,
        static_cast<int>(lua_tonumber(state, 3)),
        lua_toboolean(state, 4),
        lua_tonumber(state, 5)
        );
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
