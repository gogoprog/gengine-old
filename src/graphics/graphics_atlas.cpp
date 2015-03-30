#include "graphics_atlas.h"

#include "graphics_texture.h"
#include "debug.h"
#include "vector4.h"

namespace gengine
{
namespace graphics
{

void Atlas::init()
{
}

void Atlas::finalize()
{
}

bool Atlas::setFromTextureAndCellCount(const Texture *_texture, const uint x_cell_count, const uint y_cell_count)
{
    texture = _texture;
    uint i,j;
    Vector2 scale;
    scale.x = 1.0f / x_cell_count;
    scale.y = 1.0f / y_cell_count;

    for(j=0; j<y_cell_count; ++j)
    {
        for(i=0; i<x_cell_count; ++i)
        {
            itemTable.add(
                AtlasItem(
                    Vector2(scale.x * i, scale.y * j),
                    scale
                    )
                );
        }
    }

    return true;
}

bool Atlas::setFromTextureAndTable(const Texture *_texture, lua_State * state)
{
    texture = _texture;

    Vector2 uv_scale, uv_offset;
    Vector4 data;

    lua_pushnil(state);
    while(lua_next(state, 3) != 0)
    {
        Vector4::fill(state, data, -1);

        uv_offset.x = (1.0f / texture->getWidth()) * data.x;
        uv_offset.y = (1.0f / texture->getHeight()) * data.y;

        uv_scale.x = (1.0f / texture->getWidth()) * data.z;
        uv_scale.y = (1.0f / texture->getHeight()) * data.w;

        itemTable.add(
            AtlasItem(
                uv_offset,
                uv_scale
                )
            );

        lua_pop(state, 1);
    }
    lua_pop(state, 1);

    return true;
}

void Atlas::getDefaultExtent(Vector2 & result, const uint index) const
{
    const Vector2 & scale = getItem(index).uvScale;

    result.x = texture->getWidth() * scale.x;
    result.y = texture->getHeight() * scale.y;
}

}
}
