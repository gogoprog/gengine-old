#include "kernel/debug.h"
#include "window/window.h"
#include "core/core.h"

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
        window.init();

        unsigned long long last_ticks = 0, current_ticks;
        float dt;

        while(!core::mustQuit())
        {
            current_ticks = SDL_GetTicks();
            dt = ( current_ticks - last_ticks ) / 1000.0f;

            core::update(dt);

            window.swap();

            last_ticks = current_ticks;
        }
    }

    SDL_Quit();

    geLog("Terminated");

    return 0;
}