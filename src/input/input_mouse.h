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

    Mouse();
    SCRIPT_REGISTERER() const;

    static SCRIPT_FUNCTION(isDown);

private:
    uint
        x,
        y;
    ButtonState
        buttonStateTable[3],
        previousButtonStateTable[3];
};

}
}
