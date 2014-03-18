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
    SCRIPT_TABLE_PUSH_THIS();
    SCRIPT_TABLE_PUSH_FUNCTION(Mouse, isDown);
    SCRIPT_TABLE_PUSH_FUNCTION(Mouse, isUp);
    SCRIPT_TABLE_PUSH_FUNCTION(Mouse, getPosition);
}

SCRIPT_CLASS_FUNCTION(Mouse, isDown)
{
    SCRIPT_GET_SELF(Mouse);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == DOWN);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Mouse, isUp)
{
    SCRIPT_GET_SELF(Mouse);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == UP);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Mouse, getPosition)
{
    SCRIPT_GET_SELF(Mouse);

    SCRIPT_PUSH_NUMBER(self.x);
    SCRIPT_PUSH_NUMBER(self.y);

    return 2;
}

}
}
