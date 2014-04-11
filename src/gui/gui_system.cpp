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

        int exit_code = CefExecuteProcess(args, app.get(), nullptr);
        if (exit_code >= 0)
        {
            exit(exit_code);
            return;
        }

        handler.init();

        CefSettings settings;
        settings.single_process = true;

        CefInitialize(args, settings, app.get(), nullptr);

        delete []modified_argv;
    }
    #endif
}

void System::finalize()
{
    #ifndef EMSCRIPTEN
    {
        CefShutdown();

        handler.finalize();
    }
    #endif
}

void System::update()
{
    #ifndef EMSCRIPTEN
    {
        CefDoMessageLoopWork();
    }
    #endif
}

void System::render()
{
    #ifndef EMSCRIPTEN
    {
        handler.render();
    }
    #endif
}

void System::loadFile(const char *file_path)
{
    #ifndef EMSCRIPTEN
    {
        //browser.get()->GetMainFrame()->LoadString("Atessst", "dummy");
        browser->GetMainFrame()->LoadURL("file:///tmp/test.html");
    }
    #endif
}

}
}
