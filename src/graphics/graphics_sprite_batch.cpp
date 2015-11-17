#include "graphics_sprite_batch.h"

#include "graphics_renderer.h"
#include "graphics_atlas_item.h"
#include "graphics_atlas.h"
#include "graphics_texture.h"

namespace gengine
{
namespace graphics
{

SpriteBatch::SpriteBatch()
    :
    Object(),
    vertexCount(0),
    texture(nullptr),
    scale(Vector2::one)
{
}

Renderer::Type SpriteBatch::getRenderType()
{
    return Renderer::Type::SPRITE_BATCH;
}

void SpriteBatch::init(const uint maximum_vertex_count)
{
    vertexBuffer.init(maximum_vertex_count, false);
}

void SpriteBatch::addItem(const Atlas *atlas, const int atlas_index, const Vector2 & position, const Vector2 & extent)
{
    Vector2 half_extent = extent * 0.5f;
    const AtlasItem & atlas_item = atlas->getItem(atlas_index);
    const Vector2 & uv_offset = atlas_item.uvOffset;
    const Vector2 & uv_scale = atlas_item.uvScale;

    vertices[vertexCount].position.x = position.x - half_extent.x;
    vertices[vertexCount].position.y = position.y + half_extent.y;
    vertices[vertexCount].texCoords.u = uv_offset.x;
    vertices[vertexCount].texCoords.v = uv_offset.y;
    vertices[vertexCount].color = Vector4::one;
    ++vertexCount;

    vertices[vertexCount].position.x = position.x + half_extent.x;
    vertices[vertexCount].position.y = position.y + half_extent.y;
    vertices[vertexCount].texCoords.u = uv_scale.x + uv_offset.x;
    vertices[vertexCount].texCoords.v = uv_offset.y;
    vertices[vertexCount].color = Vector4::one;
    ++vertexCount;

    vertices[vertexCount].position.x = position.x + half_extent.x;
    vertices[vertexCount].position.y = position.y - half_extent.y;
    vertices[vertexCount].texCoords.u = uv_scale.x + uv_offset.x;
    vertices[vertexCount].texCoords.v = uv_scale.y + uv_offset.y;
    vertices[vertexCount].color = Vector4::one;
    ++vertexCount;

    vertices[vertexCount].position.x = position.x - half_extent.x;
    vertices[vertexCount].position.y = position.y - half_extent.y;
    vertices[vertexCount].texCoords.u = uv_offset.x;
    vertices[vertexCount].texCoords.v = uv_scale.y + uv_offset.y;
    vertices[vertexCount].color = Vector4::one;
    ++vertexCount;
}

void SpriteBatch::addItem(const Atlas *atlas, const int index, const Vector2 & position)
{
    const AtlasItem & atlas_item = atlas->getItem(index);
    const Vector2 & uv_scale = atlas_item.uvScale;
    const Texture & texture = atlas->getTexture();

    Vector2 extent;

    extent.x = uv_scale.x * texture.getWidth();
    extent.y = uv_scale.y * texture.getHeight();

    addItem(atlas, index, position, extent);
}

Vertex *SpriteBatch::getAddedVertices(const uint count)
{
    Vertex * result = vertices + vertexCount;

    vertexCount += 4;

    return result;
}

void SpriteBatch::lock()
{
    vertices = vertexBuffer.map();
    vertexCount = 0;
}

void SpriteBatch::unlock()
{
    vertexBuffer.unMap();
    vertices = nullptr;
}

}
}
