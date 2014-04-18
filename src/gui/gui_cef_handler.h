#pragma once

#ifndef EMSCRIPTEN

#include "primitives.h"
#include "debug.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "core_sdl.h"
#include "graphics_texture.h"
#include "graphics_shader.h"
#include "graphics_program.h"
#include "graphics_uniform.h"

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
    void update();
    void render();

    void lock();
    void unlock();

    void addTextToExecute(const char *text);

    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) override;

    CefRefPtr<CefRenderHandler> GetRenderHandler() { return this; }

    IMPLEMENT_REFCOUNTING(BrowserClient);

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
