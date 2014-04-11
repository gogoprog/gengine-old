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
        char **modified_argv;

        modified_argv = new char*[argc+1];

        for(int i=0; i<argc; ++i)
        {
            modified_argv[i] = argv[i];
        }

        modified_argv[argc] = (char*)"--disable-setuid-sandbox";

        CefMainArgs args(argc + 1, modified_argv);
        CefRefPtr<App> app(new App);
        CefSettings settings;

        CefInitialize(args, settings, app.get(), nullptr);

        delete []modified_argv;
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
