#include "gui_system.h"
#include "gui_cef_app.h"

namespace gengine
{
namespace gui
{

void System::init()
{
    #ifndef EMSCRIPTEN
    {
        CefRefPtr<App> app(new App);
        CefSettings settings;

        CefInitialize(CefMainArgs(), settings, app.get(), NULL);

        // CefRunMessageLoop();
    }
    #endif
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
