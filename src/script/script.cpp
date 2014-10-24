#include "script.h"

#include "script_system.h"
#include <string>

#ifdef EMSCRIPTEN
    #include <emscripten/bind.h>

    using namespace emscripten;
#endif

namespace gengine
{
namespace script
{

int getTableInteger(lua_State * state, const char * name, const int table_position)
{
    int result;

    lua_getfield(state, table_position, name);

    result = static_cast<int>(lua_tonumber(state, -1));

    lua_pop(state, 1);

    return result;
}

int getTableIntegerSafe(lua_State * state, const char * name, const int table_position, const int default_value)
{
    int result;

    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        result = static_cast<int>(lua_tonumber(state, -1));
    }

    lua_pop(state, 1);

    return result;
}

float getTableFloat(lua_State * state, const char * name, const int table_position)
{
    float result;

    lua_getfield(state, table_position, name);

    result = static_cast<float>(lua_tonumber(state, -1));

    lua_pop(state, 1);

    return result;
}

float getTableFloatSafe(lua_State * state, const char * name, const int table_position, const float default_value)
{
    float result;

    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        result = static_cast<float>(lua_tonumber(state, -1));
    }

    lua_pop(state, 1);

    return result;
}

void executeText(std::string text)
{
    script::System::getInstance().executeText(text.c_str());
}

#ifdef EMSCRIPTEN
    EMSCRIPTEN_BINDINGS(script_module)
    {
        function<void, std::string>("execute", &executeText);
    }
#endif

}
}

