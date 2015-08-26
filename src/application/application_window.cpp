#include "application_window.h"

#include "core_sdl.h"
#include "core.h"
#include "application.h"
#include <sstream>
#include "debug.h"
#include <GL/gl.h>

#ifdef EMSCRIPTEN
    #include <emscripten.h>
#endif

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
        Uint32 flags = 0;

        flags |= SDL_WINDOW_OPENGL;

        if(application::isFullscreen())
        {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

            // workaround for SDL bug https://bugzilla.libsdl.org/show_bug.cgi?id=3105

            SDL_DisplayMode dm;
            SDL_Event e;

            pWindow = SDL_CreateWindow("gengine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 200, SDL_WINDOW_OPENGL);
            pRenderer = SDL_CreateRenderer(
                pWindow,
                -1,
                SDL_RENDERER_ACCELERATED
                );
            context = SDL_GL_CreateContext(pWindow);

            glClear(GL_COLOR_BUFFER_BIT);
            while(SDL_PollEvent(&e));

            int display_index = SDL_GetWindowDisplayIndex(pWindow);
            SDL_GetDesktopDisplayMode(display_index, &dm);
            setExtent(dm.w, dm.h);

            SDL_GL_DeleteContext(context);
            SDL_DestroyRenderer(pRenderer);
            SDL_DestroyWindow(pWindow);
        }

        pWindow = SDL_CreateWindow(
            getName(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            getWidth(),
            getHeight(),
            flags
            );

        pRenderer = SDL_CreateRenderer(
            pWindow,
            -1,
            SDL_RENDERER_ACCELERATED
            );

        context = SDL_GL_CreateContext(pWindow);
    #else
        pWindow = SDL_SetVideoMode(
            getWidth(),
            getHeight(),
            16,
            SDL_OPENGL
            );

        std::stringstream
            text;

        text << "gengineInitialize(" << application::getWidth() << ", " << application::getHeight() << ", " << application::isFullscreen() << ");";

        emscripten_run_script(text.str().c_str());
    #endif
}

void Window::finalize()
{
    if(pWindow)
    {
        #ifndef EMSCRIPTEN
            SDL_DestroyRenderer(pRenderer);
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
