#include "debug.h"
#include "core.h"
#include "core_sdl.h"
#include "graphics_opengl.h"
#include "graphics_system.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

using namespace gengine;

unsigned long long last_ticks = 0, current_ticks;
float dt;

void loop()
{
    current_ticks = SDL_GetTicks();
    dt = ( current_ticks - last_ticks ) / 1000.0f;

    glClearColor(1.0f,current_ticks / 5000.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    core::beginUpdate(dt);

    graphics::System::getInstance().test(dt);

    core::endUpdate(dt);

    last_ticks = current_ticks;
#ifdef EMSCRIPTEN

    emscripten_pause_main_loop();
    #endif
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

    core::init();

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