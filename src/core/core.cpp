#include "core.h"

#include "core_sdl.h"
#include "input_system.h"
#include "graphics_system.h"
#include "graphics_opengl.h"
#include "application_window.h"
#include "script_system.h"
#include "entity_system.h"
#include "gui_system.h"
#include "debug.h"

namespace gengine
{
namespace core
{

void handleEvents();

bool
    itMustQuit = false;
unsigned long long
    last_ticks = 0,
    current_ticks;
application::Window
    mainWindow;

bool mustQuit()
{
    return itMustQuit;
}

application::Window getMainWindow()
{
    return mainWindow;
}

void init(int argc, char *argv[])
{
    geDebugLog("core::init()");

    gui::System::getInstance().preinit(argc,argv);

    script::System & script_system = script::System::getInstance();

    SDL_Init(SDL_INIT_VIDEO);

    script_system.init();
    script_system.executeFile("main.lua");

    script_system.call("init");

    mainWindow.init();
    graphics::System::getInstance().init();
    input::System::getInstance().init();
    entity::System::getInstance().init();
    gui::System::getInstance().init(argc,argv);

    script_system.init2();

    script_system.call("start");
}

void finalize()
{
    geDebugLog("core::finalize()");

    script::System::getInstance().call("stop");

    graphics::System::getInstance().finalize();

    mainWindow.finalize();

    script::System::getInstance().finalize();

    SDL_Quit();
}

void update()
{
    float dt;

    current_ticks = SDL_GetTicks();
    dt = ( current_ticks - last_ticks ) / 1000.0f;

    glClear(GL_COLOR_BUFFER_BIT);

    handleEvents();

    script::System::getInstance().call("update", dt);

    graphics::System::getInstance().update();

    entity::System::getInstance().update(dt);

    gui::System::getInstance().update(dt);

    graphics::System::getInstance().render();

    gui::System::getInstance().render();

    input::System::getInstance().update();

    mainWindow.swap();

    last_ticks = current_ticks;
}

void handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
            {
                itMustQuit = true;
            }
            break;

            case SDL_MOUSEMOTION:
            {
                SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent*)&e;

                input::System::getInstance().updateMouseCoordinates(0, m->x, m->y);
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&e;

                input::System::getInstance().updateMouseButton(0, m->button, input::Mouse::DOWN);
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&e;

                input::System::getInstance().updateMouseButton(0, m->button, input::Mouse::UP);
            }
            break;
        }
    }
}

}
}
