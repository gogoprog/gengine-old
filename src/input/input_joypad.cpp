#include "input_joypad.h"

#include "script.h"
#include <string.h>

namespace gengine
{
namespace input
{

Joypad::Joypad(const uint _index)
{
    memset(buttonStateTable, false, sizeof(bool) * BUTTON_COUNT);
    memset(previousButtonStateTable, false, sizeof(bool) * BUTTON_COUNT);
    index = _index;

    joystick = SDL_JoystickOpen(index);
}

Joypad::~Joypad()
{
    SDL_JoystickClose(joystick);
}

void Joypad::update()
{
    memcpy(previousButtonStateTable, buttonStateTable, sizeof(bool) * BUTTON_COUNT);
}

bool Joypad::_isJustDown(const uint button_index) const
{
    return buttonStateTable[button_index] == true && previousButtonStateTable[button_index] == false;
}

bool Joypad::_isDown(const uint button_index) const
{
    return buttonStateTable[button_index] == true;
}

bool Joypad::_isJustUp(const uint button_index) const
{
    return buttonStateTable[button_index] == false && previousButtonStateTable[button_index] == true;
}

bool Joypad::_isUp(const uint button_index) const
{
    return buttonStateTable[button_index] == false;
}

SCRIPT_CLASS_REGISTERER(Joypad) const
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_THIS();
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, isDown);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, isUp);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, isJustDown);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, isJustUp);

    lua_setfield(state, -2, "joypad");
}

SCRIPT_CLASS_FUNCTION(Joypad, isDown)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == true);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, isUp)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == false);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, isJustDown)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == true && self.previousButtonStateTable[button_index] == false);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, isJustUp)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == false && self.previousButtonStateTable[button_index] == true);

    return 1;
}

}
}
