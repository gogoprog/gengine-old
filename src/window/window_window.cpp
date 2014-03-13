#include "window_window.h"

#include "core_sdl.h"

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
        #ifndef EMSCRIPTEN
            SDL_DestroyWindow(pWindow);
        #endif
    }
}

void Window::init()
{
    #ifndef EMSCRIPTEN
        pWindow = SDL_CreateWindow(
            "An SDL2 window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_OPENGL
            );

        SDL_GLContext context = SDL_GL_CreateContext(pWindow);
        SDL_GL_MakeCurrent(pWindow, context); 
    #else
        pWindow = SDL_SetVideoMode(
            640,
            480,
            16,
            SDL_OPENGL
            );
    #endif
}

void Window::swap()
{
    #ifndef EMSCRIPTEN
        SDL_GL_SwapWindow(pWindow);
    #else
        SDL_GL_SwapBuffers();
    #endif
}

}
};