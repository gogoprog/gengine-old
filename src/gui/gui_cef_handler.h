#pragma once

#ifndef EMSCRIPTEN

#include "primitives.h"
#include "debug.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_request_handler.h"
#include "include/cef_load_handler.h"
#include "core_sdl.h"
#include "graphics_texture.h"
#include "graphics_shader.h"
#include "graphics_program.h"
#include "graphics_uniform.h"

namespace gengine
{
namespace gui
{

class Handler : public CefRenderHandler, public CefClient, public CefRequestHandler, public CefLoadHandler
{
public:
    Handler() = default;

    void init();
    void finalize();
    void update();
    void render();

    void lock();
    void unlock();

    void addTextToExecute(const char *text);

    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) override;

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override { return this; }
    virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

    virtual bool OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request) override;

    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;

    IMPLEMENT_REFCOUNTING(Handler)

private:
    graphics::Shader
        vertexShader,
        fragmentShader;
    graphics::Program
        program;
    uint
        pboId;
    graphics::Texture
        texture;
    graphics::Uniform
        samplerUniform;
    std::string
        textToExecute;

    IMPLEMENT_LOCKING(Handler)
};

}
}
#endif
