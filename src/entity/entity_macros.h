#pragma once

#define ENTITY_COMPONENT_SETTERS_START(_CLASS_) \
    SCRIPT_CLASS_FUNCTION(_CLASS_, newIndex) \
    { \
        SCRIPT_GET_SELF(_CLASS_); \
        const char * key = lua_tostring(state, 2);

#define ENTITY_COMPONENT_SETTERS_END() \
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
