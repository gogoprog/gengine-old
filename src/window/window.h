#pragma once

#ifdef EMSCRIPTEN
#define INTERNAL_FORMAT SDL_Surface
#else
#define INTERNAL_FORMAT SDL_Window
#endif

struct INTERNAL_FORMAT;

namespace gengine
{
namespace window
{

class Window
{
public:
    Window();
    ~Window();

    void init();
    void swap();

private:
    INTERNAL_FORMAT * pWindow;
};

}
};

#undef INTERNAL_FORMAT