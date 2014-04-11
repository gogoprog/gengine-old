#include "gui_system.h"

#include "gui_cef_app.h"
#include "debug.h"

namespace gengine
{
namespace gui
{

void System::init(int argc, char *argv[])
{
    geDebugLog("gui::System::init()");

    #ifndef EMSCRIPTEN
    {
        // :todo: insert --disable-setuid-sandbox
        CefMainArgs args(argc, argv);
        CefRefPtr<App> app(new App);
        CefSettings settings;

        CefInitialize(args, settings, app.get(), nullptr);
    }
    #endif
}

void System::update()
{
    CefDoMessageLoopWork();
}

void System::finalize()
{
    #ifndef EMSCRIPTEN
    {
        CefShutdown();
    }
    #endif
}

}
}
