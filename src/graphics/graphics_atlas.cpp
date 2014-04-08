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

    for(i=0; i<x_cell_count; ++i)
    {
        for(j=0; j<y_cell_count; ++j)
        {
            
        }
    }

    return true;
}

}
}
