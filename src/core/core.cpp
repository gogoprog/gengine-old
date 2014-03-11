#include "core.h"

#include <SDL2/SDL.h>

namespace gengine
{
namespace core
{

bool itMustQuit = false;

bool mustQuit()
{
    return itMustQuit;
}

void update(const float /*dt*/)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            itMustQuit = true;
        }
    }
}

}
}