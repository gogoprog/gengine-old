#include "graphics_atlas_manager.h"

#include "graphics_atlas.h"
#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

bool AtlasManager::internalCreate(Atlas * atlas, script::State state, const int parameter_position)
{
    const Texture * texture = reinterpret_cast<const Texture *>(lua_touserdata(state, 2));

    if(lua_isnumber(state, 3))
    {
        uint x = lua_tonumber(state, 3);
        uint y = lua_tonumber(state, 4);

        return atlas->setFromTextureAndCellCount(texture, x, y);
    }
    else if(lua_istable(state, 3))
    {
        lua_getfield(state, 3, "width");
        if(lua_isnil(state, -1))
        {
            lua_pop(state, 1);
            return atlas->setFromTextureAndTable(texture, state);
        }
        else
        {
            lua_pop(state, 1);
            return atlas->setFromTextureForTileset(texture, state);
        }
    }

    return false;
}

void AtlasManager::internalGetName(char * result, const char * name)
{
    strcpy(result, name);
}

}
}
