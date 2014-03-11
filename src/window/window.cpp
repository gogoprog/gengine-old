#include "window.h"

#include <SDL2/SDL.h>

namespace gengine
{
namespace window
{

Window::Window()
    :
    pWindow(nullptr)
{
}

Window::~Window()
{
    if(pWindow)
    {
        SDL_DestroyWindow(pWindow);
    }
}

void Window::init()
{
    pWindow = SDL_CreateWindow(
        "An SDL2 window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL
        );
}

void Window::swap()
{
    SDL_GL_SwapWindow(pWindow);
}

}
};