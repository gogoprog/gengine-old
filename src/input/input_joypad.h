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
        MAXIMUM_BUTTON_COUNT = 16,
        MAXIMUM_AXIS_COUNT = 6,
        MAXIMUM_HAT_COUNT = 2
    };

    Joypad() = default;
    Joypad(const uint _index);
    ~Joypad();
    SCRIPT_REGISTERER() const;

    void update();
    void connect();
    void disconnect();

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
    static SCRIPT_FUNCTION(getButtonCount);
    static SCRIPT_FUNCTION(getAxisCount);
    static SCRIPT_FUNCTION(getHatCount);

private:
    bool
        buttonStateTable[MAXIMUM_BUTTON_COUNT],
        previousButtonStateTable[MAXIMUM_BUTTON_COUNT];
    uint8
        hatValueTable[MAXIMUM_HAT_COUNT];
    float
        axisValueTable[MAXIMUM_AXIS_COUNT];
    uint8
        index;
    uint
        buttonCount,
        axisCount,
        hatCount;
};

}
}
