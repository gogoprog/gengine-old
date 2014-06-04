#include "script_system.h"

#include "script_lua.h"
#include "debug.h"
#include "application.h"
#include "graphics.h"
#include "input.h"
#include "entity.h"
#include "gui.h"
#include "audio.h"

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
    entity::luaRegister(state);
    gui::luaRegister(state);
    audio::luaRegister(state);
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

void System::executeText(const char * text)
{
    luaL_dostring(state, text);
}

void System::call(const char * name)
{
    lua_getglobal(state, name);

    call(0, 0);
}

void System::call1(const char * name, const float arg)
{
    lua_getglobal(state, name);
    lua_pushnumber(state, arg);

    call(1, 0);
}

void System::call(const uint nargs, const uint nresults)
{
    int s = lua_pcall(state, nargs, nresults, 0);

    switch(s)
    {
    case LUA_ERRRUN:
        geLog("script: runtime error");
        handleError();
        break;
    case LUA_ERRMEM:
        geLog("script: memory allocation error");
        handleError();
        break;
    default:
        break;
    }
}

void System::handleError()
{
    const char * message = lua_tostring(state, -1);
    geLog("script:" << message);
}

}
}
