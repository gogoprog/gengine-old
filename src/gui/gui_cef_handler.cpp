#ifndef EMSCRIPTEN
#include "gui_cef_handler.h"

#include "include/cef_client.h"
#include "application.h"
#include "debug.h"
#include "core.h"

namespace gengine
{
namespace gui
{

void Handler::init()
{
    surface = SDL_CreateRGBSurface(0,application::getWidth(),application::getHeight(),32,0,0,0,0);
    windowSurface = SDL_GetWindowSurface(core::getMainWindow().getSdlWindow());
}

void Handler::finalize()
{
    SDL_FreeSurface(surface);
}

void Handler::render()
{
    SDL_BlitSurface(surface, nullptr, windowSurface, nullptr);
}

bool Handler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
    rect = CefRect(0, 0, application::getWidth(), application::getHeight());
    return true;
}

void Handler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height)
{
    SDL_LockSurface(surface);

    memcpy(surface->pixels, buffer, width * height * 4);

    SDL_UnlockSurface(surface);
}

}
}
#endif
