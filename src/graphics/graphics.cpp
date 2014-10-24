#include "graphics.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_camera.h"
#include "script.h"
#include "application.h"
#include "graphics_texture_manager.h"
#include "graphics_atlas_manager.h"
#include "graphics_animation_manager.h"

namespace gengine
{
namespace graphics
{

SCRIPT_FUNCTION(setClearColor)
{
    float r,g,b,a;

    r = lua_tonumber(state, 1);
    g = lua_tonumber(state, 2);
    b = lua_tonumber(state, 3);
    a = lua_tonumber(state, 4);

    System::getInstance().setClearColor(Vector4(r,g,b,a));

    return 0;
}

SCRIPT_FUNCTION(createWorlds)
{
    System::getInstance().createWorlds(lua_tonumber(state, 1));

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_FUNCTION(setClearColor);
    SCRIPT_TABLE_PUSH_FUNCTION(createWorlds);

    TextureManager::luaRegister(state);
    lua_setfield(state, -2, "texture");

    AnimationManager::luaRegister(state);
    lua_setfield(state, -2, "animation");

    AtlasManager::luaRegister(state);
    lua_setfield(state, -2, "atlas");

    lua_setfield(state, -2, "graphics");
}

}
}
