#include "script_system.h"

#include "script_lua.h"
#include "debug.h"

namespace gengine
{
namespace script
{

void System::init()
{
    geLog("script::System::init()");

    state = luaL_newstate();
    luaL_openlibs(state);
}

void System::finalize()
{
    geLog("script::System::finalize()");

    lua_close(state);
    state = nullptr;
}

void System::executeFile(const char * file)
{
    int s = luaL_loadfile(state, file);

    if(!s)
    {
        s = lua_pcall(state, 0, LUA_MULTRET, 0);
    }
}

void System::call(const char * name, const float arg)
{
    lua_getglobal(state, name);
    lua_pushnumber(state, arg);

    lua_pcall(state, 1, 0, 0);
}

}
}
