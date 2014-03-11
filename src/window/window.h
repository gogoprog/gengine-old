#pragma once

struct SDL_Window;

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
    SDL_Window * pWindow;
};

}
};