#pragma once

#include "script_lua.h"
#include "vector2.h"
#include "vector4.h"

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
    int _name_(lua_State * state)

#define SCRIPT_CLASS_FUNCTION(_class_, _name_) \
    int _class_::_name_(lua_State * state)

#define SCRIPT_REGISTER(_name_) \
    lua_register(state, #_name_, &_name_)

#define SCRIPT_GET_SELF(_class_) \
    SCRIPT_TABLE_GET_THIS(_class_)

#define SCRIPT_TABLE_GET_THIS(_class_) \
    lua_getfield(state, 1, "this"); \
    _class_ & self = * static_cast<_class_*>(lua_touserdata(state, -1))

#define SCRIPT_TABLE_PUSH_FUNCTION(_name_) \
    lua_pushcfunction(state, &_name_); \
    lua_setfield(state, -2, #_name_)

#define SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, _name_) \
    lua_pushcfunction(state, &_class_::_name_); \
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


namespace gengine
{
namespace script
{

void fillVector2(lua_State * state, Vector2 & result, int position = -1);
void fillTableVector2Safe(lua_State * state, Vector2 & result, const char * name, int position = -1, const Vector2 default_value = Vector2::zero);
void fillVector4(lua_State * state, Vector4 & result, int position = -1);
void fillTableVector4Safe(lua_State * state, Vector4 & result, const char * name, int position = -1, const Vector4 default_value = Vector4::zero);
int getTableInteger(lua_State * state, const char * name, const int table_position = -1);
int getTableIntegerSafe(lua_State * state, const char * name, const int table_position = -1, const int default_value = 0);
float getTableFloat(lua_State * state, const char * name, const int table_position = -1);
float getTableFloatSafe(lua_State * state, const char * name, const int table_position = -1, const float default_value = 0.0f);

}
}
