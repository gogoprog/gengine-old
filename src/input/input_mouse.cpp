#include "input_mouse.h"

#include "script.h"
#include "debug.h"
#include <string.h>

namespace gengine
{
namespace input
{

Mouse::Mouse()
    :
    x(0),
    y(0)
{
    memset(buttonStateTable, 0, sizeof(ButtonState) * BUTTON_COUNT);
    memset(previousButtonStateTable, 0, sizeof(ButtonState) * BUTTON_COUNT);
}

bool Mouse::_isJustDown(const uint button_index) const
{
    return buttonStateTable[button_index] == DOWN && previousButtonStateTable[button_index] == UP;
}

bool Mouse::_isDown(const uint button_index) const
{
    return buttonStateTable[button_index] == DOWN;
}

SCRIPT_CLASS_REGISTERER(Mouse) const
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_THIS();
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Mouse, isDown);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Mouse, isUp);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Mouse, isJustDown);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Mouse, isJustUp);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Mouse, getPosition);
}

SCRIPT_CLASS_FUNCTION(Mouse, isDown)
{
    SCRIPT_TABLE_GET_THIS(Mouse);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == DOWN);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Mouse, isUp)
{
    SCRIPT_TABLE_GET_THIS(Mouse);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == UP);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Mouse, isJustDown)
{
    SCRIPT_TABLE_GET_THIS(Mouse);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == DOWN && self.previousButtonStateTable[button_index] == UP);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Mouse, isJustUp)
{
    SCRIPT_TABLE_GET_THIS(Mouse);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == UP && self.previousButtonStateTable[button_index] == DOWN);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Mouse, getPosition)
{
    SCRIPT_TABLE_GET_THIS(Mouse);

    SCRIPT_PUSH_NUMBER(self.x);
    SCRIPT_PUSH_NUMBER(self.y);

    return 2;
}

}
}
