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

    for(uint i=0; i<JOYPAD_COUNT; ++i)
    {
        joypadTable.add(Joypad(i));
    }
}

void System::finalize()
{
    mouseTable.setSize(0);

    for(Joypad & joypad : joypadTable)
    {
        if(joypad.isConnected())
        {
            joypad.disconnect();
        }
    }

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

void System::updateJoypadButton(const int id, const uint button_index, const bool state)
{
    if(button_index < Joypad::BUTTON_COUNT)
    {
        joypadTable[joypadIdMap[id]].buttonStateTable[button_index] = state;
    }
}

void System::onJoypadConnected(const int index)
{
    joypadTable[index].connect();
    joypadIdMap.add(index, joypadTable[index].joystickId);
}

void System::onJoypadDisconnected(const int index)
{
    joypadIdMap.remove(joypadTable[index].joystickId);
    joypadTable[index].disconnect();
}

void System::update()
{
    for(Mouse & mouse : mouseTable)
    {
        mouse.update();
    }

    for(Joypad & joypad : joypadTable)
    {
        joypad.update();
    }

    keyboard.update();
}

}
}
