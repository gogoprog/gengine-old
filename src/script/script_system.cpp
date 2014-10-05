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

    lua_newtable(state);

    SCRIPT_DO(
        return function(_class)
            _class.onStateEnter = {}
            setmetatable(_class.onStateEnter, { __index = function(t,k) return function() end end })
            _class.onStateUpdate = {}
            setmetatable(_class.onStateUpdate, { __index = function(t,k) return function() end end })
            _class.onStateExit = {}
            setmetatable(_class.onStateExit, { __index = function(t,k) return function() end end })

            _class.changeState = function(s, state)
                local old_state = s.state
                s.state = nil
                s.onStateExit[old_state](s)
                s.onStateEnter[state](s)
                s.state = state
            end

            _class.updateState = function(s, ...)
                s.onStateUpdate[s.state](s, ...)
            end
        end
        );

    lua_setfield(state, -2, "stateMachine");

    SCRIPT_DO(
        return function(key, value, t)
            for i=1,t do io.write("    ") end
            print(key)
            for i=1,t+1 do io.write("    ") end
            print("Functions:")
            for k, v in pairs(value) do
                if type(v) == "function" and k:sub(1,2) ~= "__" then
                    for i=1,t+2 do io.write("    ") end
                    print(k.."(...)")
                end
            end
            local first = true
            for k, v in pairs(value) do
                if type(v) == "table" then
                    if first then
                        for i=1,t+1 do io.write("    ") end
                        print("Subtables:")
                        first = false
                    end
                    gengine.describeTable(k, v, t+2)
                end
            end
        end
        );

    lua_setfield(state, -2, "describeTable");

    SCRIPT_DO(
        return function()
            print("Help:")
            print("    Components:")
            for k, v in pairs(_G) do
                if k:sub(1,9) == "Component" then
                    gengine.describeTable(k, v, 2)
                end
            end
            gengine.describeTable("gengine:", gengine, 1)
        end
        );

    lua_setfield(state, -2, "help");

    application::luaRegister(state);

    lua_setglobal(state, "gengine");

    SCRIPT_DO(
        function __init()
            debug = debug or require("debug")
            require("mobdebug").start()
        end
        pcall(__init)
        );
}

void System::finalize()
{
    geDebugLog("script::System::finalize()");

    lua_close(state);
    state = nullptr;
}

void System::init2()
{
    lua_getglobal(state, "gengine");

    graphics::luaRegister(state);
    input::luaRegister(state);
    entity::luaRegister(state);
    gui::luaRegister(state);
    audio::luaRegister(state);

    lua_pop(state, 1);
}

void System::executeFile(const char * file)
{
    luaL_loadfile(state, file);

    call(0, LUA_MULTRET);
}

void System::executeText(const char * text)
{
    static std::string before("return function() ");
    static std::string after(" end");
    luaL_dostring(state, (before + text + after).c_str());
    call(0, 0);
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
