#include "input_system.h"

#include "core_sdl.h"
#include "debug.h"

namespace gengine
{
namespace input
{

void System::init()
{
    geDebugLog("input::System::init()");

    mouseTable.add(Mouse());

    uint joypad_count = SDL_NumJoysticks();

    for(uint i=0; i<joypad_count; ++i)
    {
        joypadTable.add(new Joypad(i));
    }
}

void System::finalize()
{
    mouseTable.setSize(0);
    joypadTable.setSize(0);
}

void System::updateMouseCoordinates(const int index, const int x, const int y)
{
    Mouse & mouse = mouseTable[index];
    mouse.x = x;
    mouse.y = y;
}

void System::updateMouseButton(const int index, const int button_index, const Mouse::ButtonState state)
{
    Mouse & mouse = mouseTable[index];
    mouse.buttonStateTable[button_index] = state;
}

void System::updateKeyboardState(const int key_index, const bool state)
{
    if(key_index < Keyboard::KEY_COUNT)
    {
        keyboard.keyStateTable[key_index] = state;
    }
}

void System::updateJoypadButton(const int index, const uint button_index, const bool state)
{
    if(button_index < Joypad::BUTTON_COUNT)
    {
        joypadTable[index]->buttonStateTable[button_index] = state;
    }
}

void System::update()
{
    for(Mouse & mouse : mouseTable)
    {
        mouse.update();
    }

    keyboard.update();
}

}
}
