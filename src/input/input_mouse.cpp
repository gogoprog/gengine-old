#include "input_mouse.h"

#include "script.h"
#include "debug.h"

namespace gengine
{
namespace input
{

Mouse::Mouse()
    :
    x(0),
    y(0)
{
}

SCRIPT_CLASS_REGISTERER(Mouse) const
{
    lua_newtable(state);
    lua_pushlightuserdata(state, (void*)(this));
    lua_setfield(state, -2, "this");
    SCRIPT_PUSH_FUNCTION(Mouse, isDown);
}

SCRIPT_CLASS_FUNCTION(Mouse, isDown)
{
    SCRIPT_GET_SELF(Mouse);

    uint button_index = lua_tonumber(state,2);

    lua_pushboolean(state, self.buttonStateTable[button_index] == DOWN);

    return 1;
}

}
}
