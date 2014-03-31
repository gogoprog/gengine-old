#include "graphics_texture_manager.h"

#include "debug.h"

namespace gengine
{
namespace graphics
{

SCRIPT_CLASS_REGISTERER(TextureManager)
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(TextureManager, load);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(TextureManager, get);
}

SCRIPT_CLASS_FUNCTION(TextureManager, load)
{
    const char * name = lua_tostring(state, 1);
    Texture * texture = new Texture();

    texture->init();
    texture->setFromFile(name);

    getInstance().textureMap.add(texture, name);

    lua_pushlightuserdata(state, texture);

    return 1;
}

SCRIPT_CLASS_FUNCTION(TextureManager, get)
{
    const char * name = lua_tostring(state, 1);
    Texture * texture;

    if(getInstance().textureMap.find(texture, name))
    {
        lua_pushlightuserdata(state, texture);
    }
    else
    {
        lua_pushnil(state);
    }

    return 1;
}

}
}
