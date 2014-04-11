#pragma once

#include "primitives.h"
#include "gui_cef_handler.h"

namespace gengine
{
namespace gui
{

class System
{
public:
    SINGLETON(System);

    void init(int argc, char *argv[]);
    void finalize();
    void update();
    void render();

#ifndef EMSCRIPTEN
    Handler & getHandler() { return handler; }

private:
    Handler handler;
#endif
};

}
}
