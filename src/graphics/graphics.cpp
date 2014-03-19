#include "graphics.h"

#include "graphics_system.h"
#include "script.h"

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

    graphics::System::getInstance().setClearColor(Vector4(r,g,b,a));

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_FUNCTION(setClearColor);
    lua_setglobal(state,"graphics");
}

}
}
