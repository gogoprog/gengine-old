#pragma once

#include "script_lua.h"
#include "script_binder.h"

#define SCRIPT_DEBUG_TOP() \
    geDebugLog(lua_gettop(state))

#define SCRIPT_REGISTERER() \
    void luaRegister(lua_State * state)

#define SCRIPT_UNREGISTERER() \
    void luaUnregister(lua_State * state)

#define SCRIPT_CLASS_REGISTERER(_name_) \
    void _name_::luaRegister(lua_State * state)

#define SCRIPT_CLASS_UNREGISTERER(_name_) \
    void _name_::luaUnregister(lua_State * state)

#define SCRIPT_FUNCTION(_name_) \
    int _##_name_(lua_State * state)

#define SCRIPT_CLASS_FUNCTION(_class_, _name_) \
    int _class_::_##_name_(lua_State * state)

#define SCRIPT_REGISTER(_name_) \
    lua_register(state, #_name_, &_##_name_)

#define SCRIPT_GET_SELF(_class_) \
    SCRIPT_TABLE_GET_THIS(_class_)

#define SCRIPT_TABLE_GET_THIS(_class_) \
    lua_getfield(state, 1, "this"); \
    _class_ & self = * static_cast<_class_*>(lua_touserdata(state, -1))

#define SCRIPT_TABLE_PUSH_FUNCTION(_name_) \
    lua_pushcfunction(state, &_##_name_); \
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_FUNCTION2(_function_, _name_) \
    lua_pushcfunction(state, &_##_function_); \
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, _name_) \
    lua_pushcfunction(state, &_class_::_##_name_); \
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_INTERNAL_FUNCTION(_name_) \
    lua_pushcfunction(state, &_##_name_); \
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_NUMBER(_name_, _value_) \
    lua_pushnumber(state, _value_);\
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_STRING(_name_, _value_) \
    lua_pushstring(state, _value_);\
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_THIS() \
    lua_pushlightuserdata(state, (void*)(this)); \
    lua_setfield(state, -2, "this");

#define SCRIPT_PUSH_BOOL(_value_) \
    lua_pushboolean(state, _value_);

#define SCRIPT_PUSH_NUMBER(_value_) \
    lua_pushnumber(state, _value_);

#define SCRIPT_DO(...) \
    luaL_dostring(state, #__VA_ARGS__);


namespace gengine
{
namespace script
{

typedef lua_State *
    State;

int getTableInteger(lua_State * state, const char * name, const int table_position = -1);
int getTableIntegerSafe(lua_State * state, const char * name, const int table_position = -1, const int default_value = 0);
float getTableFloat(lua_State * state, const char * name, const int table_position = -1);
float getTableFloatSafe(lua_State * state, const char * name, const int table_position = -1, const float default_value = 0.0f);

void executeText(const char * text);

template<class T>
void get(lua_State * state, T & result, const int position = -1)
{
    Binder<T>::get(state, result, position);
}

inline void get(lua_State * state, float & result, const int position = -1)
{
    result = lua_tonumber(state, position);
}

template<class T>
void push(lua_State * state, const T & value)
{
    Binder<T>::push(state, value);
}

inline void push(lua_State * state, const float value)
{
    lua_pushnumber(state, value);
}

template<class T>
void update(lua_State * state, const T & value)
{
    Binder<T>::update(state, value);
}

}
}
