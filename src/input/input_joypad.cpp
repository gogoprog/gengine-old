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
}

Joypad::~Joypad()
{
}

void Joypad::update()
{

}

void Joypad::connect()
{
}

void Joypad::disconnect()
{
    // SDL_JoystickClose(joystick); // :todo: figure out what to do.
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


}
}
