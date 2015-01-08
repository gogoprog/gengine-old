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
}

Joypad::~Joypad()
{
}

void Joypad::update()
{
    if(joystick)
    {
        memcpy(previousButtonStateTable, buttonStateTable, sizeof(bool) * BUTTON_COUNT);
    }
}

void Joypad::connect()
{
    joystick = SDL_JoystickOpen(index);
}

void Joypad::disconnect()
{
    SDL_JoystickClose(joystick);
    joystick = nullptr;
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

    lua_rawseti(state, -2, index);
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
