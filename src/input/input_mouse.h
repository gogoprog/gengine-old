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
        BUTTON_COUNT = 3
    };

    Mouse();
    SCRIPT_REGISTERER() const;

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
