#pragma once

#include "primitives.h"
#include "script.h"

namespace gengine
{
namespace input
{

class Mouse
{
    friend class System;

public:
    enum ButtonState
    {
        UP,
        DOWN
    };

    enum
    {
        BUTTON_FIRST = 1,
        BUTTON_LAST = 3,
        BUTTON_COUNT
    };

    Mouse();
    SCRIPT_REGISTERER() const;

    void update();

    uint getX() const { return x; }
    uint getY() const { return y; }
    bool _isJustDown(const uint button_index) const;
    bool _isDown(const uint button_index) const;
    bool _isJustUp(const uint button_index) const;
    bool _isUp(const uint button_index) const;

    static SCRIPT_FUNCTION(isDown);
    static SCRIPT_FUNCTION(isUp);
    static SCRIPT_FUNCTION(isJustDown);
    static SCRIPT_FUNCTION(isJustUp);
    static SCRIPT_FUNCTION(getPosition);

private:
    uint
        x,
        y;
    ButtonState
        buttonStateTable[BUTTON_COUNT],
        previousButtonStateTable[BUTTON_COUNT];
};

}
}
