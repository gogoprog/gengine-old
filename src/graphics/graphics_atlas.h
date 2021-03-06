#pragma once

#include "primitives.h"
#include "graphics_atlas_item.h"
#include "script.h"
#include "array.h"
#include "pointer.h"

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
    bool setFromTextureAndCellCount(const Texture *texture, const uint x_cell_count, const uint y_cell_count);
    bool setFromTextureAndTable(const Texture *texture, script::State state);
    bool setFromTextureForTileset(const Texture *texture, script::State state);

    uint getSize() const { return itemTable.getSize(); }
    AtlasItem & getItem(const uint index) { return itemTable[index]; }
    const AtlasItem & getItem(const uint index) const { return itemTable[index]; }
    const Texture & getTexture() const { return *texture; }
    bool hasTexture() const { return !texture.isNull(); }

    void getDefaultExtent(math::Vector2 & result, const uint index) const;

private:
    Array<AtlasItem>
        itemTable;
    Pointer<const Texture>
        texture;
};

}
}
