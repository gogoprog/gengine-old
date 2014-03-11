#include "kernel/debug.h"

#include <SDL2/SDL.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

int main()
{
    lua_State *state;

    geLog("Started");

    state = luaL_newstate();
    luaL_openlibs(state);

    int s = luaL_loadfile(state, "main.lua");

    if(s==0)
    {
        s = lua_pcall(state, 0, LUA_MULTRET, 0);
    }

    return 0;
}