#pragma once

#include "kernel/primitives.h"

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

    bool isDown(const int index) const;
    bool isUp(const int index) const;


private:
    uint x,y;
    ButtonState buttonStateTable[3], previousButtonStateTable[3];
};

}
}
