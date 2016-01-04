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

class LocalV8Handler : public CefV8Handler {
public:
    LocalV8Handler() {}

    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE
    {
        gui::System::getInstance().getHandler().addTextToExecute(arguments[0]->GetStringValue().ToString().c_str());
        return true;
    }

    IMPLEMENT_REFCOUNTING(LocalV8Handler);
};

void App::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    CefRefPtr<CefV8Value> global_object = context->GetGlobal();
    CefRefPtr<CefV8Value> gengine_object = CefV8Value::CreateObject(nullptr);
    CefRefPtr<CefV8Value> execute_func = CefV8Value::CreateFunction("gengine_execute", new LocalV8Handler());

    gengine_object->SetValue("execute", execute_func, V8_PROPERTY_ATTRIBUTE_NONE);

    global_object->SetValue("gengine", gengine_object, V8_PROPERTY_ATTRIBUTE_NONE);
}

void App::OnContextInitialized()
{
    CefWindowInfo window_info;

    window_info.SetAsOffScreen(nullptr);
    window_info.SetTransparentPainting(true);

    CefBrowserSettings browser_settings;

    System::getInstance().browser = CefBrowserHost::CreateBrowserSync(window_info, & System::getInstance().getHandler(), "about:blank", browser_settings, nullptr);
}

void App::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar)
{
}

}
}
#endif
