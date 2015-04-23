#pragma once

#include "primitives.h"
#include "script.h"

namespace gengine
{
namespace input
{

class Keyboard
{
    friend class System;

public:
    enum
    {
        KEY_COUNT = 282
    };

    Keyboard();
    SCRIPT_REGISTERER() const;

    bool isJustDown(const uint key_index) const;
    bool isDown(const uint key_index) const;
    bool isJustUp(const uint key_index) const;
    bool isUp(const uint key_index) const;

    void update();

    static SCRIPT_FUNCTION(isDown);
    static SCRIPT_FUNCTION(isUp);
    static SCRIPT_FUNCTION(isJustDown);
    static SCRIPT_FUNCTION(isJustUp);

private:
    bool
        keyStateTable[KEY_COUNT],
        previousKeyStateTable[KEY_COUNT];
};

}
}
