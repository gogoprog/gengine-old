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

private:
    #ifndef EMSCRIPTEN
        SDL_Window * pWindow;
        SDL_GLContext context;
    #else
        SDL_Surface * pWindow;
    #endif
};

}
}
