#pragma once

#include "core_sdl.h"

namespace gengine
{
namespace application
{

class Window
{
public:
    Window();
    ~Window();

    void init();
    void finalize();
    void swap();


    #ifndef EMSCRIPTEN
        SDL_Window * getSdlWindow() { return pWindow; }
        SDL_Renderer * getSdlRenderer() { return pRenderer; }
    #endif

private:
    #ifndef EMSCRIPTEN
        SDL_Window
            * pWindow;
        SDL_Renderer
            * pRenderer;
		SDL_GLContext
			context;
    #else
        SDL_Surface
            * pWindow;
    #endif
};

}
}
