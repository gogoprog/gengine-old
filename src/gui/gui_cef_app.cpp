#ifndef EMSCRIPTEN
#include "gui_cef_app.h"

#include "gui_system.h"
#include "include/cef_client.h"
#include "application.h"
#include "debug.h"

namespace gengine
{
namespace gui
{

void App::OnContextInitialized()
{
    CefWindowInfo window_info;

    window_info.SetAsOffScreen(nullptr);

    CefRefPtr<Handler> handler(& System::getInstance().getHandler());

    CefBrowserSettings browser_settings;

    std::string url = "http://gogopr.org";

    CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings, nullptr);
}

}
}
#endif
