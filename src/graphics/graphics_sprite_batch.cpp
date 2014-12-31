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
    Object()
{
}

Renderer::Type SpriteBatch::getRenderType()
{
    return Renderer::Type::SPRITE_BATCH;
}

void SpriteBatch::init()
{
    vertexData.reserve(128);
}

void SpriteBatch::addItem(const int index, const Vector2 & position, const Vector2 & extent)
{
    Vertex vertices[4];

    Vector2 half_extent = extent * 0.5f;
    const AtlasItem & atlas_item = atlas->getItem(index);
    const Vector2 & uv_offset = atlas_item.uvOffset;
    const Vector2 & uv_scale = atlas_item.uvScale;

    vertices[0].position.x = position.x - half_extent.x;
    vertices[0].position.y = position.y + half_extent.y;
    vertices[0].texCoords.u = uv_offset.x;
    vertices[0].texCoords.v = uv_offset.y;

    vertices[1].position.x = position.x + half_extent.x;
    vertices[1].position.y = position.y + half_extent.y;
    vertices[1].texCoords.u = uv_scale.x + uv_offset.x;
    vertices[1].texCoords.v = uv_offset.y;

    vertices[2].position.x = position.x + half_extent.x;
    vertices[2].position.y = position.y - half_extent.y;
    vertices[2].texCoords.u = uv_scale.x + uv_offset.x;
    vertices[2].texCoords.v = uv_scale.y + uv_offset.y;

    vertices[3].position.x = position.x - half_extent.x;
    vertices[3].position.y = position.y - half_extent.y;
    vertices[3].texCoords.u = uv_offset.x;
    vertices[3].texCoords.v = uv_scale.y + uv_offset.y;

    for(uint i=0; i<4; ++i)
    {
        vertexData.add(vertices[i]);
    }
}

void SpriteBatch::addItem(const int index, const Vector2 & position)
{
    const AtlasItem & atlas_item = atlas->getItem(index);
    const Vector2 & uv_scale = atlas_item.uvScale;
    const Texture & texture = atlas->getTexture();

    Vector2 extent;

    extent.x = uv_scale.x * texture.getWidth();
    extent.y = uv_scale.y * texture.getHeight();

    addItem(index, position, extent);
}

void SpriteBatch::reserve(const int size)
{
    vertexData.reserve(size * 4);
}

void SpriteBatch::lock()
{

    vertexData.setSize(0);
}

void SpriteBatch::unlock()
{
    vertexBuffer.init();
    vertexBuffer.setData(& vertexData[0], vertexData.getSize());
}

}
}
