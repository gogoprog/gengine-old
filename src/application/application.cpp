#include "application.h"

#include "primitives.h"
#include "script.h"
#include "core.h"
#include <string>

namespace gengine
{
namespace application
{

std::string
    name = "gengine";
bool
    fullscreen = false;
uint
    width = 640,
    height = 480;

SCRIPT_FUNCTION(setName)
{
    name = lua_tostring(state, 1);

    return 0;
}

SCRIPT_FUNCTION(setExtent)
{
    width = uint(lua_tonumber(state, 1));
    height = uint(lua_tonumber(state, 2));

    return 0;
}

SCRIPT_FUNCTION(setFullscreen)
{
    fullscreen = lua_toboolean(state, 1);

    return 0;
}

SCRIPT_FUNCTION(setUpdateFactor)
{
    float factor = uint(lua_tonumber(state, 1));

    core::setUpdateFactor(factor);

    return 0;
}

SCRIPT_FUNCTION(quit)
{
    core::setMustQuit(true);
    return 0;
}

const char * getName() { return name.c_str(); }
uint getWidth() { return width; }
uint getHeight() { return height; }
math::Vector2 getExtent() { return math::Vector2(width, height); }
void setExtent(const uint _width, const uint _height) { width = _width; height = _height; }
bool isFullscreen() { return fullscreen; }

SCRIPT_REGISTERER()
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_FUNCTION(setName);
    SCRIPT_TABLE_PUSH_FUNCTION(setExtent);
    SCRIPT_TABLE_PUSH_FUNCTION(setFullscreen);
    SCRIPT_TABLE_PUSH_FUNCTION(setUpdateFactor);
    SCRIPT_TABLE_PUSH_FUNCTION(quit);
    lua_setfield(state, -2, "application");
}

}
}
