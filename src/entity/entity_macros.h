#pragma once


#define ENTITY_COMPONENT_DECLARE() \
    static SCRIPT_REGISTERER(); \
    static SCRIPT_FUNCTION(create); \
    static SCRIPT_FUNCTION(newIndex); \
    static SCRIPT_FUNCTION(init); \
    static SCRIPT_FUNCTION(insert); \
    static SCRIPT_FUNCTION(update); \
    static SCRIPT_FUNCTION(remove); \
    static uint \
        metaTableRef;

#define ENTITY_COMPONENT_IMPLEMENT(_CLASS_) \
    SCRIPT_CLASS_FUNCTION(_CLASS_, create) \
    { \
        return System::getInstance().createComponent<_CLASS_>(state); \
    } \
    uint \
        _CLASS_::metaTableRef; \
    SCRIPT_CLASS_REGISTERER(_CLASS_)

#define ENTITY_COMPONENT_PUSH_FUNCTION(_FUNCTION_) \
    SCRIPT_TABLE_PUSH_INTERNAL_FUNCTION(_FUNCTION_)

#define ENTITY_COMPONENT_SETTERS(_CLASS_) \
    SCRIPT_CLASS_FUNCTION(_CLASS_, newIndex) \
    { \
        SCRIPT_GET_SELF(_CLASS_); \
        const char * key = lua_tostring(state, 2);

#define ENTITY_COMPONENT_END() \
        return 0; \
    }

#define ENTITY_COMPONENT_SETTER(_NAME_) \
     if(!strcmp(key, #_NAME_))

#define ENTITY_COMPONENT_SETTER_DEFAULT() \
    else

#define ENTITY_COMPONENT_SETTER_END() \
    else \
    { \
        geLog("Unknown attribute \"" << key << "\""); \
    }

#define ENTITY_COMPONENT_METHOD(_CLASS_, _METHOD_) \
    SCRIPT_CLASS_FUNCTION(ComponentCamera, _METHOD_) \
    { \
        SCRIPT_GET_SELF(ComponentCamera); \
        (void)self; (void)state;

