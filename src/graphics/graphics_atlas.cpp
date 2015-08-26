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
    math::Vector2 scale;
    scale.x = 1.0f / x_cell_count;
    scale.y = 1.0f / y_cell_count;

    for(j=0; j<y_cell_count; ++j)
    {
        for(i=0; i<x_cell_count; ++i)
        {
            itemTable.add(
                AtlasItem(
                    math::Vector2(scale.x * i, scale.y * j),
                    scale
                    )
                );
        }
    }

    return true;
}

bool Atlas::setFromTextureAndTable(const Texture *_texture, script::State state)
{
    texture = _texture;

    math::Vector2 uv_scale, uv_offset;
    math::Vector4 data;

    lua_pushnil(state);
    while(lua_next(state, 3) != 0)
    {
        math::Vector4::fill(state, data, -1);

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

bool Atlas::setFromTextureForTileset(const Texture *_texture, script::State state)
{
    uint width, height, margin, spacing;

    texture = _texture;

    lua_getfield(state, 3, "width");
    script::get(state, width, -1, 0);
    lua_pop(state, 1);

    lua_getfield(state, 3, "height");
    script::get(state, height, -1, 0);
    lua_pop(state, 1);

    lua_getfield(state, 3, "spacing");
    script::get(state, spacing, -1, 0);
    lua_pop(state, 1);

    lua_getfield(state, 3, "margin");
    script::get(state, margin, -1, 0);
    lua_pop(state, 1);

    if(width && height)
    {
        uint texture_width, texture_height;
        math::Vector2 uv_scale, uv_offset;

        texture_width = texture->getWidth();
        texture_height = texture->getHeight();

        uv_scale.x = width / (float)texture_width;
        uv_scale.y = height / (float)texture_height;

        for(uint y=margin; y<=texture_height-height-margin; y+=spacing+height)
        {
            for(uint x=margin; x<=texture_width-width-margin; x+=spacing+width)
            {
                uv_offset.x = x / (float)texture_width;
                uv_offset.y = y / (float)texture_height;

                itemTable.add(
                    AtlasItem(
                        uv_offset,
                        uv_scale
                        )
                    );
            }
        }

        return true;
    }

    return false;
}

void Atlas::getDefaultExtent(math::Vector2 & result, const uint index) const
{
    const math::Vector2 & scale = getItem(index).uvScale;

    result.x = texture->getWidth() * scale.x;
    result.y = texture->getHeight() * scale.y;
}

}
}
