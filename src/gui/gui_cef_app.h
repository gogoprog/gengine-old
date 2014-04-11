#pragma once

#ifndef EMSCRIPTEN

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

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE { return this; }
    virtual void OnContextInitialized() OVERRIDE;

private:

    IMPLEMENT_REFCOUNTING(SimpleApp);
};

}
}
#endif
