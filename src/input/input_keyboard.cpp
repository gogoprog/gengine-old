#include "input_keyboard.h"

#include "script.h"
#include <string.h>

namespace gengine
{
namespace input
{

Keyboard::Keyboard()
{
    memset(keyStateTable, false, sizeof(bool) * KEY_COUNT);
    memset(previousKeyStateTable, false, sizeof(bool) * KEY_COUNT);
}

void Keyboard::update()
{
    memcpy(previousKeyStateTable, keyStateTable, sizeof(bool) * KEY_COUNT );
}

bool Keyboard::isJustDown(const uint key_index) const
{
    return keyStateTable[key_index] == true && previousKeyStateTable[key_index] == false;
}

bool Keyboard::isDown(const uint key_index) const
{
    return keyStateTable[key_index] == true;
}

bool Keyboard::isJustUp(const uint key_index) const
{
    return keyStateTable[key_index] == false && previousKeyStateTable[key_index] == true;
}

bool Keyboard::isUp(const uint key_index) const
{
    return keyStateTable[key_index] == false;
}

SCRIPT_CLASS_REGISTERER(Keyboard) const
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_THIS();
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Keyboard, isDown);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Keyboard, isUp);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Keyboard, isJustDown);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(Keyboard, isJustUp);

    lua_setfield(state, -2, "keyboard");
}

SCRIPT_CLASS_FUNCTION(Keyboard, isDown)
{
    SCRIPT_TABLE_GET_THIS(Keyboard);

    uint key_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.keyStateTable[key_index] == true);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Keyboard, isUp)
{
    SCRIPT_TABLE_GET_THIS(Keyboard);

    uint key_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.keyStateTable[key_index] == false);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Keyboard, isJustDown)
{
    SCRIPT_TABLE_GET_THIS(Keyboard);

    uint key_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.keyStateTable[key_index] == true && self.previousKeyStateTable[key_index] == false);

    return 1;
}

SCRIPT_CLASS_FUNCTION(Keyboard, isJustUp)
{
    SCRIPT_TABLE_GET_THIS(Keyboard);

    uint key_index = lua_tonumber(state,2);

    SCRIPT_PUSH_BOOL(self.keyStateTable[key_index] == false && self.previousKeyStateTable[key_index] == true);

    return 1;
}

}
}
