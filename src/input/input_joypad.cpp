#include "input_joypad.h"

#include "script.h"
#include <string.h>

namespace gengine
{
namespace input
{

Joypad::Joypad(const uint _index)
    : buttonCount(0), axisCount(0), hatCount(0)
{
    memset(buttonStateTable, false, sizeof(bool) * MAXIMUM_BUTTON_COUNT);
    memset(previousButtonStateTable, false, sizeof(bool) * MAXIMUM_BUTTON_COUNT);
    index = _index;
}

Joypad::~Joypad()
{
}

void Joypad::update()
{
    if(joystick)
    {
        memcpy(previousButtonStateTable, buttonStateTable, sizeof(bool) * MAXIMUM_BUTTON_COUNT);
    }
}

void Joypad::connect()
{
    joystick = SDL_JoystickOpen(index);
    joystickId = SDL_JoystickInstanceID(joystick);
    buttonCount = SDL_JoystickNumButtons(joystick);
    axisCount = SDL_JoystickNumAxes(joystick);
    hatCount = SDL_JoystickNumHats(joystick);
}

void Joypad::disconnect()
{
    // SDL_JoystickClose(joystick); // :todo: figure out what to do.
    joystick = nullptr;
    joystickId = -1;
}

bool Joypad::isJustDown(const uint button_index) const
{
    return buttonStateTable[button_index] == true && previousButtonStateTable[button_index] == false;
}

bool Joypad::isDown(const uint button_index) const
{
    return buttonStateTable[button_index] == true;
}

bool Joypad::isJustUp(const uint button_index) const
{
    return buttonStateTable[button_index] == false && previousButtonStateTable[button_index] == true;
}

bool Joypad::isUp(const uint button_index) const
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
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, isConnected);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, getAxis);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, getHat);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, getButtonCount);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, getAxisCount);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Joypad, getHatCount);

    lua_rawseti(state, -2, index);
}

SCRIPT_CLASS_FUNCTION(Joypad, isDown)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state, 2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == true);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, isUp)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state, 2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == false);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, isJustDown)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state, 2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == true && self.previousButtonStateTable[button_index] == false);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, isJustUp)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint button_index = lua_tonumber(state, 2);

    SCRIPT_PUSH_BOOL(self.buttonStateTable[button_index] == false && self.previousButtonStateTable[button_index] == true);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, isConnected)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    SCRIPT_PUSH_BOOL(self.isConnected());

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, getAxis)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint axis_index = lua_tonumber(state, 2);

    SCRIPT_PUSH_NUMBER(self.axisValueTable[axis_index]);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, getHat)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    uint hat_index = lua_tonumber(state, 2);

    SCRIPT_PUSH_NUMBER(self.hatValueTable[hat_index]);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, getButtonCount)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    SCRIPT_PUSH_NUMBER(self.buttonCount);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, getAxisCount)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    SCRIPT_PUSH_NUMBER(self.axisCount);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Joypad, getHatCount)
{
    SCRIPT_TABLE_GET_THIS(Joypad);

    SCRIPT_PUSH_NUMBER(self.hatCount);

    return 1;
}

}
}
