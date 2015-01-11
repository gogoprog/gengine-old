#pragma once

#include "primitives.h"
#include "script.h"
#include "core_sdl.h"
#include "pointer.h"

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
        BUTTON_COUNT = 16,
        HAT_COUNT = 1
    };

    Joypad() = default;
    Joypad(const uint _index);
    ~Joypad();
    SCRIPT_REGISTERER() const;

    void update();
    void connect();
    void disconnect();

    bool isConnected() const { return !joystick.isNull(); }

    bool isJustDown(const uint key_index) const;
    bool isDown(const uint key_index) const;
    bool isJustUp(const uint key_index) const;
    bool isUp(const uint key_index) const;

    static SCRIPT_FUNCTION(isDown);
    static SCRIPT_FUNCTION(isUp);
    static SCRIPT_FUNCTION(isJustDown);
    static SCRIPT_FUNCTION(isJustUp);
    static SCRIPT_FUNCTION(isConnected);
    static SCRIPT_FUNCTION(getAxis);
    static SCRIPT_FUNCTION(getHat);

private:
    bool
        buttonStateTable[BUTTON_COUNT],
        previousButtonStateTable[BUTTON_COUNT];
    uint8
        hatValueTable[HAT_COUNT];
    float
        axisValueTable[2];
    uint8
        index;
    Pointer<SDL_Joystick>
        joystick;
    SDL_JoystickID
        joystickId;
};

}
}
