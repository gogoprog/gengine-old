#include "graphics_atlas_manager.h"

#include "graphics_atlas.h"
#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

void AtlasManager::init()
{

}

void AtlasManager::finalize()
{
    for(auto & kv : atlasMap)
    {
        kv.second->finalize();
        delete kv.second;
    }
}

SCRIPT_CLASS_REGISTERER(AtlasManager)
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(AtlasManager, create);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(AtlasManager, get);
}

SCRIPT_CLASS_FUNCTION(AtlasManager, create)
{
    const char * name = lua_tostring(state, 1);
    const Texture * texture = reinterpret_cast<const Texture *>(lua_touserdata(state, 2));
    uint x = lua_tonumber(state, 3);
    uint y = lua_tonumber(state, 4);

    Atlas * atlas = new Atlas();

    atlas->init();
    
    if(atlas->setFromTexture(texture, x, y))
    {
        getInstance().atlasMap.add(atlas, name);
        lua_pushlightuserdata(state, atlas);
    }
    else
    {
        atlas->finalize();
        delete atlas;
        lua_pushnil(state);
    }

    return 1;
}

SCRIPT_CLASS_FUNCTION(AtlasManager, get)
{
    const char * name = lua_tostring(state, 1);
    Atlas * atlas;

    if(getInstance().atlasMap.find(atlas, name))
    {
        lua_pushlightuserdata(state, atlas);
    }
    else
    {
        lua_pushnil(state);
    }

    return 1;
}

}
}
