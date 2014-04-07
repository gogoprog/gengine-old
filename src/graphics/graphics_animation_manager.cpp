#include "graphics_animation_manager.h"

#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

void AnimationManager::init()
{

}

void AnimationManager::finalize()
{
    for(auto & kv : animationMap)
    {
        kv.second->finalize();
        delete kv.second;
    }
}

SCRIPT_CLASS_REGISTERER(AnimationManager)
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(AnimationManager, load);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(AnimationManager, get);
}

SCRIPT_CLASS_FUNCTION(AnimationManager, load)
{
    const char * name = lua_tostring(state, 1);
    Animation * animation = new Animation();

    animation->init();
    
    if(animation->setFromTable(state))
    {
        getInstance().animationMap.add(animation, name);
        lua_pushlightuserdata(state, animation);
    }
    else
    {
        animation->finalize();
        delete animation;
        lua_pushnil(state);
    }

    return 1;
}

SCRIPT_CLASS_FUNCTION(AnimationManager, get)
{
    const char * name = lua_tostring(state, 1);
    Animation * texture;

    if(getInstance().animationMap.find(texture, name))
    {
        lua_pushlightuserdata(state, texture);
    }
    else
    {
        lua_pushnil(state);
    }

    return 1;
}

void AnimationManager::getBaseName(char * result, const char * file_path)
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
