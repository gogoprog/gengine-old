#include "core.h"

#include "core/sdl.h"
#include "input/system.h"

namespace gengine
{
namespace core
{

bool itMustQuit = false;

bool mustQuit()
{
    return itMustQuit;
}

void init()
{
    input::System::getInstance().init();
}

void update(const float /*dt*/)
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