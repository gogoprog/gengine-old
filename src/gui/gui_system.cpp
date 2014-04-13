#include "gui_system.h"

#include "gui_cef_app.h"
#include "debug.h"
#include "unistd.h"
#include "input_mouse.h"
#include "input_system.h"

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
        settings.multi_threaded_message_loop = false;

        CefInitialize(args, settings, app.get(), nullptr);

        delete []modified_argv;

        timeSinceLastUpdate = 0.0f;
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

void System::update(const float dt)
{
    #ifndef EMSCRIPTEN
    {
        timeSinceLastUpdate += dt;

        {
            static CefMouseEvent last_mouse_event;

            CefMouseEvent mouse_event;
            const input::Mouse & mouse = input::System::getInstance().getMouse(0);

            mouse_event.x = mouse.getX();
            mouse_event.y = mouse.getY();

            if(mouse._isJustDown(1))
            {
                browser->GetHost()->SendMouseClickEvent(mouse_event, MBT_LEFT, false, 1);
            }

            if(mouse._isJustUp(1))
            {
                browser->GetHost()->SendMouseClickEvent(mouse_event, MBT_LEFT, true, 1);
            }

            if(mouse._isDown(3))
            {
                browser->GetHost()->SendMouseMoveEvent(mouse_event, true);
            }
        }

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
    geDebugLog("gui::System::loadFile \"" << file_path << "\"");

    #ifndef EMSCRIPTEN
    {
        char cwd[1024];
        std::string url;
        url = "file://";

        if(file_path[0] != '/')
        {
            url += getcwd(cwd, 1024);
            url += "/";
        }

        url += file_path;

        browser->GetMainFrame()->LoadURL(url);
    }
    #endif
}

}
}
