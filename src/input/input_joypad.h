#pragma once

#include "primitives.h"
#include "script.h"
#include "core_sdl.h"

namespace gengine
{
namespace input
{

class Joypad
{
    friend class System;

public:
    enum
    {
        BUTTON_COUNT = 16
    };

    Joypad() = default;
    Joypad(const uint _index);
    ~Joypad();
    SCRIPT_REGISTERER() const;

    bool _isJustDown(const uint key_index) const;
    bool _isDown(const uint key_index) const;
    bool _isJustUp(const uint key_index) const;
    bool _isUp(const uint key_index) const;

    void update();

    static SCRIPT_FUNCTION(isDown);
    static SCRIPT_FUNCTION(isUp);
    static SCRIPT_FUNCTION(isJustDown);
    static SCRIPT_FUNCTION(isJustUp);

private:
    bool
        buttonStateTable[BUTTON_COUNT],
        previousButtonStateTable[BUTTON_COUNT];
    uint
        index;
    SDL_Joystick
        * joystick;
};

}
}
