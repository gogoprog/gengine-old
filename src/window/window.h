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
    void Init();

private:
    SDL_Window * pWindow;
};

}
};