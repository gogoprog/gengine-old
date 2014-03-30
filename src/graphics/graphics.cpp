#include "graphics.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_camera.h"
#include "script.h"
#include "application.h"
#include "graphics_texture_manager.h"

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

SCRIPT_FUNCTION(getWorldPosition)
{
    Vector2 pos;

    pos.x = lua_tonumber(state, 1);
    pos.y = lua_tonumber(state, 2);

    Camera & camera =  System::getInstance().getWorld(0).getCurrentCamera();

    pos.x += camera.getPosition().x - camera.getExtent().x * 0.5f;
    pos.y = application::getHeight() - pos.y - camera.getExtent().y * 0.5f;;
    pos.y += camera.getPosition().y;

    SCRIPT_PUSH_NUMBER(pos.x);
    SCRIPT_PUSH_NUMBER(pos.y);

    return 2;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_FUNCTION(setClearColor);
    SCRIPT_TABLE_PUSH_FUNCTION(getWorldPosition);
    
    TextureManager::luaRegister(state);
    lua_setfield(state, -2, "texture");


    lua_setglobal(state,"graphics");
}

}
}
