#ifndef EMSCRIPTEN
#include "gui_cef_app.h"

#include "include/cef_client.h"
#include "application.h"
#include "debug.h"

namespace gengine
{
namespace gui
{

class RenderHandler : public CefRenderHandler
{
public:
    RenderHandler() = default;

    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
    {
        rect = CefRect(0, 0, application::getWidth(), application::getHeight());
        return true;
    }

    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height)
    {
        geDebugLog("OnPaint");
    }

    IMPLEMENT_REFCOUNTING(RenderHandler);

};

class BrowserClient : public CefClient
{
public:
    BrowserClient()
    {
        renderHandler = new RenderHandler();
    }

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() {
        return renderHandler;
    }

    CefRefPtr<CefRenderHandler> renderHandler;

    IMPLEMENT_REFCOUNTING(BrowserClient);
};


void App::OnContextInitialized()
{
    CefWindowInfo window_info;

    window_info.SetAsOffScreen(nullptr);

    CefRefPtr<BrowserClient> handler(new BrowserClient());

    CefBrowserSettings browser_settings;

    std::string url = "http://gogopr.org";

    CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings, nullptr);
}

}
}
#endif
