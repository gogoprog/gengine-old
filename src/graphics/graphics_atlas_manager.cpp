#include "graphics_atlas_manager.h"

#include "graphics_atlas.h"
#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

bool AtlasManager::internalCreate(Atlas * atlas, script::State state)
{
    const Texture * texture = reinterpret_cast<const Texture *>(lua_touserdata(state, 2));
    uint x = lua_tonumber(state, 3);
    uint y = lua_tonumber(state, 4);

    return atlas->setFromTexture(texture, x, y);
}

void AtlasManager::internalGetName(char * result, const char * name)
{
    strcpy(result, name);
}

}
}
