#pragma once

#include "map.h"
#include <functional>


#define ENTITY_GETTER_MAP_TYPE(_CLASS_) \
    Map<std::string, std::function<void(lua_State *, const _CLASS_ &)> >

#define ENTITY_COMPONENT_DECLARE(_CLASS_) \
    static SCRIPT_REGISTERER(); \
    static SCRIPT_FUNCTION(create); \
    static SCRIPT_FUNCTION(newIndex); \
    static SCRIPT_FUNCTION(index); \
    static SCRIPT_FUNCTION(init); \
    static SCRIPT_FUNCTION(insert); \
    static SCRIPT_FUNCTION(update); \
    static SCRIPT_FUNCTION(remove); \
    static uint \
        metaTableRef; \
    static ENTITY_GETTER_MAP_TYPE(_CLASS_) \
        getterMap;

#define ENTITY_COMPONENT_IMPLEMENT(_CLASS_) \
    SCRIPT_CLASS_FUNCTION(_CLASS_, index) \
    { \
        SCRIPT_GET_SELF(_CLASS_); \
        const char * name = lua_tostring(state, 2);\
        getterMap[name](state, self);\
        return 1;\
    } \
    SCRIPT_CLASS_FUNCTION(_CLASS_, create) \
    { \
        return System::getInstance().createComponent<_CLASS_>(state); \
    } \
    uint \
        _CLASS_::metaTableRef; \
    ENTITY_GETTER_MAP_TYPE(_CLASS_) \
        _CLASS_::getterMap; \
    SCRIPT_CLASS_REGISTERER(_CLASS_)

#define ENTITY_COMPONENT_PUSH_FUNCTION(_FUNCTION_) \
    SCRIPT_TABLE_PUSH_INTERNAL_FUNCTION(_FUNCTION_)

#define ENTITY_ADD_GETTER(_CLASS_, _NAME_, _FUNCTION_BODY_) \
    getterMap.add( \
        [&](lua_State *state, const _CLASS_ & self) _FUNCTION_BODY_, \
        _NAME_ \
        );

#define ENTITY_COMPONENT_SETTERS(_CLASS_) \
    SCRIPT_CLASS_FUNCTION(_CLASS_, newIndex) \
    { \
        SCRIPT_GET_SELF(_CLASS_); \
        const char * key = lua_tostring(state, 2);

#define ENTITY_COMPONENT_SETTER_FIRST(_NAME_) \
     if(!strcmp(key, #_NAME_))

#define ENTITY_COMPONENT_SETTER(_NAME_) \
     else if(!strcmp(key, #_NAME_))

#define ENTITY_COMPONENT_SETTER_DEFAULT() \
    else

#define ENTITY_COMPONENT_SETTER_END() \
    else \
    { \
        geLog("Unknown attribute \"" << key << "\""); \
    }

#define ENTITY_COMPONENT_METHOD(_CLASS_, _METHOD_) \
    SCRIPT_CLASS_FUNCTION(_CLASS_, _METHOD_) \
    { \
        SCRIPT_GET_SELF(_CLASS_); \
        (void)self; (void)state;

#define ENTITY_COMPONENT_METHOD_DECLARE(_METHOD_) \
     static SCRIPT_FUNCTION(_METHOD_);

#define ENTITY_COMPONENT_END() \
        return 0; \
    }
