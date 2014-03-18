#include "application_window.h"

#include "core_sdl.h"
#include "application.h"

namespace gengine
{
namespace application
{

Window::Window()
    :
    pWindow(nullptr)
{
}

Window::~Window()
{
}

void Window::init()
{
    #ifndef EMSCRIPTEN
        pWindow = SDL_CreateWindow(
            getName(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            getWidth(),
            getHeight(),
            SDL_WINDOW_OPENGL
            );

        context = SDL_GL_CreateContext(pWindow);
        SDL_GL_MakeCurrent(pWindow, context); 
    #else
        pWindow = SDL_SetVideoMode(
            getWidth(),
            getHeight(),
            16,
            SDL_OPENGL
            );
    #endif
}

void Window::finalize()
{
    if(pWindow)
    {
        #ifndef EMSCRIPTEN
            SDL_GL_DeleteContext(context);
            SDL_DestroyWindow(pWindow);
        #endif
    }
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