#pragma once

#include "script_lua.h"

#define SCRIPT_REGISTERER() void luaRegister(lua_State * state)
#define SCRIPT_CLASS_REGISTERER(_name_) void _name_::luaRegister(lua_State * state)
#define SCRIPT_FUNCTION(_name_) int _name_(lua_State * state)
#define SCRIPT_REGISTER(_name_) lua_register(state, #_name_, &_name_)
