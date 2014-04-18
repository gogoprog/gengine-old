#pragma once

#ifndef EMSCRIPTEN

#define CEF_ENABLE_SANDBOX 0

#include "primitives.h"
#include "include/cef_app.h"
namespace gengine
{
namespace gui
{

class App : public CefApp, public CefBrowserProcessHandler
{
public:
    App() = default;

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
    virtual void OnContextInitialized() override;
    virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) override;

private:

    IMPLEMENT_REFCOUNTING(SimpleApp);
};

}
}
#endif
