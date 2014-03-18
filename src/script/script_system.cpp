#include "script_system.h"

#include "script_lua.h"
#include "debug.h"
#include "application.h"
#include "graphics.h"
#include "input.h"

namespace gengine
{
namespace script
{

void System::init()
{
    geDebugLog("script::System::init()");

    state = luaL_newstate();
    luaL_openlibs(state);

    application::luaRegister(state);
}

void System::finalize()
{
    geDebugLog("script::System::finalize()");

    lua_close(state);
    state = nullptr;
}

void System::init2()
{
    graphics::luaRegister(state);
    input::luaRegister(state);
}

void System::executeFile(const char * file)
{
    int s = luaL_loadfile(state, file);

    if(!s)
    {
        s = lua_pcall(state, 0, LUA_MULTRET, 0);

        if(s)
        {
            handleError();
        }
    }
    else
    {
        handleError();
    }
}

void System::call(const char * name)
{
    lua_getglobal(state, name);

    internalCall(0);
}

void System::call(const char * name, const float arg)
{
    lua_getglobal(state, name);
    lua_pushnumber(state, arg);

    internalCall(1);
}

void System::internalCall(const uint arg_count)
{
    int s = lua_pcall(state, arg_count, 0, 0);

    if(s)
    {
        handleError();
    }
}

void System::handleError()
{
    const char * message = lua_tostring(state, -1);
    geLog("script:" << message);
}

}
}
