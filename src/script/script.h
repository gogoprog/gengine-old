#pragma once

#include "script_lua.h"

#define SCRIPT_REGISTERER() \
    void luaRegister(lua_State * state)

#define SCRIPT_CLASS_REGISTERER(_name_) \
    void _name_::luaRegister(lua_State * state)

#define SCRIPT_FUNCTION(_name_) \
    int _name_(lua_State * state)

#define SCRIPT_CLASS_FUNCTION(_class_, _name_) \
    int _class_::_name_(lua_State * state)

#define SCRIPT_REGISTER(_name_) \
    lua_register(state, #_name_, &_name_)

#define SCRIPT_GET_SELF(_class_) \
    lua_getfield(state, 1, "this"); \
    _class_ & self = * static_cast<_class_*>(lua_touserdata(state, -1))

#define SCRIPT_TABLE_PUSH_FUNCTION(_name_) \
    lua_pushcfunction(state, &_name_); \
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, _name_) \
    lua_pushcfunction(state, &_class_::_name_); \
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_THIS() \
    lua_pushlightuserdata(state, (void*)(this)); \
    lua_setfield(state, -2, "this");

#define SCRIPT_PUSH_BOOL(_value_) \
    lua_pushboolean(state, _value_);

#define SCRIPT_PUSH_NUMBER(_value_) \
    lua_pushnumber(state, _value_);
