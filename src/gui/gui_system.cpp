#include "gui_system.h"

#include "gui_cef_app.h"
#include "debug.h"
#include "input_mouse.h"
#include "input_system.h"
#include "application.h"

#include <sstream>

#ifdef _WINDOWS
    #include <direct.h>
#else
    #include "unistd.h"
#endif

#define JAVASCRIPT(src) \
    #src

#ifdef EMSCRIPTEN
    #include <emscripten.h>
#endif

namespace gengine
{
namespace gui
{

void System::preinit(int argc, char *argv[])
{
    geDebugLog("gui::System::preinit()");

    #ifndef EMSCRIPTEN
    {
        #ifdef _LINUX
            CefMainArgs args(argc, argv);
        #elif defined(_WINDOWS)
            CefMainArgs args(GetModuleHandle(NULL));
        #endif

        CefRefPtr<App> app(new App);

        int exit_code = CefExecuteProcess(args, app.get(), nullptr);

        if (exit_code >= 0)
        {
            exit(exit_code);
            return;
        }
    }
    #endif
}

void System::init(int argc, char *argv[])
{
    geDebugLog("gui::System::init()");

    #ifndef EMSCRIPTEN
    {
        #ifdef _LINUX
            CefMainArgs args(argc, argv);
        #elif defined(_WINDOWS)
            CefMainArgs args(GetModuleHandle(NULL));
        #endif

        CefRefPtr<App> app(new App);

        handler.init();

        CefSettings settings;
        memset(&settings, 0, sizeof(CefSettings));
        settings.single_process = true;
        settings.no_sandbox = true;
        settings.multi_threaded_message_loop = false;
        settings.size = sizeof(CefSettings);

        CefInitialize(args, settings, app.get(), nullptr);

        timeSinceLastUpdate = 0.0f;
    }
    #else
    {
        std::stringstream
            text;

        text << "document.getElementById('canvas_holder').style.width = '";
        text << application::getWidth();
        text << "px'; ";

        text << "document.getElementById('canvas_holder').style.height = '";
        text << application::getHeight();
        text << "px';";

        emscripten_run_script(text.str().c_str());
    }
    #endif
}

void System::finalize()
{
    #ifndef EMSCRIPTEN
    {
        handler.finalize();

        CefQuitMessageLoop();
        CefShutdown();
    }
    #endif
}

void System::update(const float dt)
{
    #ifndef EMSCRIPTEN
    {
        timeSinceLastUpdate += dt;

        {
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

            #ifdef _WINDOWS // note: required since there is a bug in CEF on Linux
            {
                browser->GetHost()->SendMouseMoveEvent(mouse_event, false);
            }
            #endif
        }

        CefDoMessageLoopWork();

        handler.update();
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
            #ifdef _WINDOWS
                url += _getcwd(cwd, 1024);
            #else
                url += getcwd(cwd, 1024);
            #endif

            url += "/";
        }

        url += file_path;

        browser->GetMainFrame()->LoadURL(url);
    }
    #else
    {
        std::string js_code;

        js_code = "loadFile('";
        js_code += file_path;
        js_code += "');";

        emscripten_run_script(js_code.c_str());
    }
    #endif
}

void System::executeScript(const char *code)
{
    #ifndef EMSCRIPTEN
    {
        CefRefPtr<CefFrame> frame = browser->GetMainFrame();
        frame->ExecuteJavaScript(code, frame->GetURL(), 0);
    }
    #else
    {
        emscripten_run_script(code);
    }
    #endif
}


}
}
