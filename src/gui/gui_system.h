#pragma once

#include "primitives.h"
#include "gui_cef_handler.h"

namespace gengine
{
namespace gui
{

class System
{
    friend class App;

public:
    SINGLETON(System);

    void preinit(int argc, char *argv[]);
    void init(int argc, char *argv[]);
    void finalize();
    void update(const float dt);
    void render();
    void loadFile(const char *file_path);
    void executeScript(const char *code);

#ifndef EMSCRIPTEN
    Handler & getHandler() { return handler; }

private:
    Handler
        handler;
    CefRefPtr<CefBrowser>
        browser;
    float
        timeSinceLastUpdate;
#endif
};

}
}
