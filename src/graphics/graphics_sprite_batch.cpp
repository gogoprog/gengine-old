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
    itemCount( 0 )
{
}

Renderer::Type SpriteBatch::getRenderType()
{
    return Renderer::Type::SPRITE_BATCH;
}

void SpriteBatch::init(const uint size)
{
    maximumItemCount = size;
    vertexBuffer.init(size * 4, false);
}

void SpriteBatch::addItem(const int atlas_index, const Vector2 & position, const Vector2 & extent)
{
    Vector2 half_extent = extent * 0.5f;
    const AtlasItem & atlas_item = atlas->getItem(atlas_index);
    const Vector2 & uv_offset = atlas_item.uvOffset;
    const Vector2 & uv_scale = atlas_item.uvScale;

    vertices[itemCount * 4 + 0].position.x = position.x - half_extent.x;
    vertices[itemCount * 4 + 0].position.y = position.y + half_extent.y;
    vertices[itemCount * 4 + 0].texCoords.u = uv_offset.x;
    vertices[itemCount * 4 + 0].texCoords.v = uv_offset.y;

    vertices[itemCount * 4 + 1].position.x = position.x + half_extent.x;
    vertices[itemCount * 4 + 1].position.y = position.y + half_extent.y;
    vertices[itemCount * 4 + 1].texCoords.u = uv_scale.x + uv_offset.x;
    vertices[itemCount * 4 + 1].texCoords.v = uv_offset.y;

    vertices[itemCount * 4 + 2].position.x = position.x + half_extent.x;
    vertices[itemCount * 4 + 2].position.y = position.y - half_extent.y;
    vertices[itemCount * 4 + 2].texCoords.u = uv_scale.x + uv_offset.x;
    vertices[itemCount * 4 + 2].texCoords.v = uv_scale.y + uv_offset.y;

    vertices[itemCount * 4 + 3].position.x = position.x - half_extent.x;
    vertices[itemCount * 4 + 3].position.y = position.y - half_extent.y;
    vertices[itemCount * 4 + 3].texCoords.u = uv_offset.x;
    vertices[itemCount * 4 + 3].texCoords.v = uv_scale.y + uv_offset.y;

    ++itemCount;
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
}

void SpriteBatch::lock()
{
    vertices = vertexBuffer.map();
    itemCount = 0;
}

void SpriteBatch::unlock()
{
    vertexBuffer.unMap();
    vertices = nullptr;
}

}
}
