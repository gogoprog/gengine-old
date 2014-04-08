#pragma once

#include "primitives.h"
#include "graphics_atlas_item.h"
#include "script.h"
#include "array.h"

namespace gengine
{
namespace graphics
{

class Texture;

class Atlas
{
friend class AtlasManager;

public:
    Atlas() = default;
    void init();
    void finalize();
    bool setFromTexture(const Texture *texture, const uint x_cell_count, const uint y_cell_count);

private:
    Array<AtlasItem>
        itemTable;
    const Texture
        * texture;
};

}
}
