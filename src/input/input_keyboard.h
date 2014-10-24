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

    bool _isJustDown(const uint key_index) const;
    bool _isDown(const uint key_index) const;
    bool _isJustUp(const uint key_index) const;
    bool _isUp(const uint key_index) const;

    void update();

    static SCRIPT_FUNCTION(isDown);
    static SCRIPT_FUNCTION(isUp);
    static SCRIPT_FUNCTION(isJustDown);
    static SCRIPT_FUNCTION(isJustUp);
    static SCRIPT_FUNCTION(getPosition);

private:
    bool
        keyStateTable[KEY_COUNT],
        previousKeyStateTable[KEY_COUNT];
};

}
}
