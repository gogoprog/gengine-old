#include "script_system.h"

#include "script_lua.h"
#include "debug.h"
#include "application.h"
#include "graphics.h"
#include "input.h"
#include "entity.h"
#include "gui.h"
#include "audio.h"

extern "C" {
#include "../../deps/common/libluasocket/luasocket.h"
}

#define PRELOAD(name, function) \
    lua_getglobal(state, "package"); \
    lua_getfield(state, -1, "preload"); \
    lua_pushcfunction(state, function); \
    lua_setfield(state, -2, name); \
    lua_pop(state, 2);  

int __open_luasocket_socket(lua_State * L)
{
    #include "../../deps/common/libluasocket/socket.lua.h"
    lua_getglobal(L, "socket");
    return 1;
}


namespace gengine
{
namespace script
{

void System::init()
{
    geDebugLog("script::System::init()");

    state = luaL_newstate();
    luaL_openlibs(state);

    PRELOAD("socket.core", luaopen_socket_core);

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
    luaL_loadfile(state, file);

    call(0, LUA_MULTRET);
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
    int status;
    int base = lua_gettop(state) - nargs;
    lua_pushcfunction(state, System::traceBack);
    lua_insert(state, base);
    status = lua_pcall(state, nargs, nresults, base);
    lua_remove(state, base);

    switch(status)
    {
    case LUA_ERRRUN:
        geLog("script: runtime error");
        break;
    case LUA_ERRMEM:
        geLog("script: memory allocation error");
        break;
    default:
        break;
    }
}

int System::traceBack(lua_State *state)
{
    const char *msg = lua_tostring(state, 1);
    if (msg)
    {
        luaL_traceback(state, state, msg, 1);
    }
    else if (!lua_isnoneornil(state, 1))
    {
        if (!luaL_callmeta(state, 1, "__tostring"))
        {
            lua_pushliteral(state, "(no error message)");
        }
    }

    const char *bt = lua_tostring(state, -1);
    geLog(bt);

    return 1;
}


}
}
