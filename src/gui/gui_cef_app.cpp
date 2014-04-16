#ifndef EMSCRIPTEN
#include "gui_cef_app.h"

#include "gui_system.h"
#include "include/cef_client.h"
#include "application.h"
#include "debug.h"
#include "script_system.h"

namespace gengine
{
namespace gui
{

// Implementation of the resource handler for client requests.
class LocalResourceHandler : public CefResourceHandler
{
public:
    LocalResourceHandler() {}

    virtual bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) override
    {
        std::string
            code;

        code = request->GetURL().ToString();

        code = code.substr(10);

        script::System::getInstance().executeText(code.c_str());

        return true;
    }

    virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) override
    {
        response->SetMimeType("text/html");
        response->SetStatus(200);
        response_length = 0;
    }

    virtual void Cancel() override
    {
    }

    virtual bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback) override
    {
        return false;
    }

private:
    IMPLEMENT_REFCOUNTING(LocalResourceHandler);
};

class LocalSchemeHandlerFactory : public CefSchemeHandlerFactory
{
public:
    virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override
    {
        return new LocalResourceHandler();
    }

    IMPLEMENT_REFCOUNTING(LocalSchemeHandlerFactory);
};

void App::OnContextInitialized()
{
    CefWindowInfo window_info;

    window_info.SetAsOffScreen(nullptr);
    window_info.SetTransparentPainting(true);

    CefRegisterSchemeHandlerFactory("gengine", "gengine", new LocalSchemeHandlerFactory());

    CefRefPtr<Handler> handler(& System::getInstance().getHandler());

    CefBrowserSettings browser_settings;

    System::getInstance().browser = CefBrowserHost::CreateBrowserSync(window_info, handler.get(), "about:blank", browser_settings, nullptr);
}

void App::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar)
{
}

}
}
#endif
