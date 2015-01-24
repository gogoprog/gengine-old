#pragma once

#include "input_mouse.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "primitives.h"
#include "array.h"
#include "map.h"

namespace gengine
{
namespace input
{

class System
{
public:
    enum
    {
        JOYPAD_COUNT = 4
    };

    SINGLETON(System);
    const Mouse & getMouse(const int index) const { return mouseTable[index]; }
    const Keyboard & getKeyboard() const { return keyboard; }
    const Joypad & getJoypad(const int index) const { return joypadTable[index]; }

    void init();
    void finalize();
    void updateMouseCoordinates(const int index, const int x, const int y);
    void updateMouseButton(const int index, const int button_index, const Mouse::ButtonState state);
    void updateMouseWheel(const int index, const int wheel);
    void updateKeyboardState(const int key_index, const bool state);
    void updateJoypadButton(const int id, const uint button_index, const bool state);
    void updateJoypadAxis(const int id, const uint axis, const float value);
    void updateJoypadHat(const int id, const uint hat, const uint value);
    void onJoypadConnected(const int index);
    void onJoypadDisconnected(const int index);
    void update();

private:
    Array<Mouse>
        mouseTable;
    Array<Joypad>
        joypadTable;
    Map<SDL_JoystickID, uint>
        joypadIdMap;
    Keyboard
        keyboard;
};

}
}
