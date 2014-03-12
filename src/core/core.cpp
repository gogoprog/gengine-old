#include "core.h"

#include "core_sdl.h"
#include "input_system.h"
#include "graphics_system.h"
#include "window_window.h"

namespace gengine
{
namespace core
{

bool itMustQuit = false;
window::Window mainWindow;

bool mustQuit()
{
    return itMustQuit;
}

void init()
{
    mainWindow.init();
    graphics::System::getInstance().init();
    input::System::getInstance().init();
}

void beginUpdate(const float /*dt*/)
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

void endUpdate(const float /*dt*/)
{
    mainWindow.swap();
}

}
}