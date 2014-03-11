#include "kernel/debug.h"
#include "window/window.h"
#include "core/core.h"
#include "core/sdl.h"
#include "graphics/opengl.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

using namespace gengine;

window::Window mainWindow;
unsigned long long last_ticks = 0, current_ticks;
float dt;

void loop()
{
    current_ticks = SDL_GetTicks();
    dt = ( current_ticks - last_ticks ) / 1000.0f;

    core::update(dt);

    mainWindow.swap();

    last_ticks = current_ticks;
}

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

    mainWindow.init();

    #ifndef EMSCRIPTEN
        while(!core::mustQuit())
        {
            loop();
        }

        SDL_Quit();

        geLog("Terminated");
    #else
        emscripten_set_main_loop(loop, 0, 0);
    #endif

    return 0;
}