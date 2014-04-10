#include "graphics_atlas.h"

#include "debug.h"

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

bool Atlas::setFromTexture(const Texture *_texture, const uint x_cell_count, const uint y_cell_count)
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

}
}
