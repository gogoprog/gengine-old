#include "kernel/debug.h"
#include "window/window.h"

#include <SDL2/SDL.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace gengine;

int main()
{
    lua_State *state;

    geLog("Init SDL");

    SDL_Init( SDL_INIT_VIDEO );

    geLog("Init Lua");
    state = luaL_newstate();
    luaL_openlibs(state);

    int s = luaL_loadfile(state, "main.lua");

    if(!s)
    {
        s = lua_pcall(state, 0, LUA_MULTRET, 0);
    }

    {
        window::Window window;
        window.Init();

        SDL_Delay(3000);
    }

    SDL_Quit();

    geLog("Terminated");

    return 0;
}