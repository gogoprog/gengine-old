#pragma once

#ifndef EMSCRIPTEN

#include "primitives.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "core_sdl.h"

namespace gengine
{
namespace gui
{

class Handler : public CefRenderHandler, public CefClient
{
public:
    Handler() = default;

    void init();
    void finalize();
    void render();

    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) override;
    
    CefRefPtr<CefRenderHandler> GetRenderHandler() { return this; }

    IMPLEMENT_REFCOUNTING(BrowserClient);

private:
    SDL_Surface
        * surface,
        * windowSurface;
};

}
}
#endif
