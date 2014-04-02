#include "graphics_texture_manager.h"

#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

void TextureManager::init()
{

}

void TextureManager::finalize()
{
    for(auto & kv : textureMap)
    {
        kv.second->finalize();
        delete kv.second;
    }
}

SCRIPT_CLASS_REGISTERER(TextureManager)
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(TextureManager, load);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(TextureManager, get);
}

SCRIPT_CLASS_FUNCTION(TextureManager, load)
{
    const char * file_path = lua_tostring(state, 1);
    Texture * texture = new Texture();
    char name[128];

    texture->init();
    
    if(texture->setFromFile(file_path))
    {
        getBaseName(name, file_path);
        getInstance().textureMap.add(texture, name);
        lua_pushlightuserdata(state, texture);
    }
    else
    {
        texture->finalize();
        delete texture;
        lua_pushnil(state);
    }

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

void TextureManager::getBaseName(char * result, const char * file_path)
{
    const char * begin, * end;
    uint length;

    if(!(begin = strchr(file_path,'/')))
    {
        begin = file_path;
    }

    if(!(end = strrchr(begin,'.')))
    {
        end = begin + strlen(begin);
    }

    length = end - begin;

    strncpy(result, begin, length);
    result[length] = 0;
}

}
}
