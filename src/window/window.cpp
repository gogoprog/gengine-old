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
    Init();
}

Window::~Window()
{
    if(pWindow)
    {
        SDL_DestroyWindow(pWindow);
    }
}

void Window::Init()
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

}
};