#ifndef EMSCRIPTEN
#include "gui_cef_handler.h"

#include "include/cef_client.h"
#include "application.h"
#include "debug.h"
#include "core.h"
#include "script_system.h"
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Graphics.h>

#ifdef _WINDOWS
    #include <direct.h>
#else
    #include "unistd.h"
#endif

namespace gengine
{
namespace gui
{

Handler::Handler()
{
}

void Handler::init()
{
    uint width = application::getWidth();
    uint height = application::getHeight();

    texture = new Urho3D::Texture2D(&core::getContext());
    texture->SetMipsToSkip(Urho3D::QUALITY_LOW, 0);
    texture->SetNumLevels(1);
    texture->SetSize(width, height, Urho3D::Graphics::GetRGBAFormat());

    auto sprite = new Urho3D::Sprite(&core::getContext());
    sprite->SetTexture(texture);
    sprite->SetSize(Urho3D::IntVector2(width, height));
    sprite->SetHotSpot(Urho3D::IntVector2(0, 0));
    sprite->SetColor(Urho3D::Color(1.0f, 1.0f, 1.0f, 1.0f));
    sprite->SetBlendMode(Urho3D::BLEND_ALPHA);
    core::getUI().GetRoot()->AddChild(sprite);
}

void Handler::finalize()
{
}

void Handler::update()
{
    if(textToExecute.size())
    {
        lock();
        script::System::getInstance().executeText(textToExecute.c_str());
        textToExecute.clear();
        unlock();
    }
}

void Handler::lock()
{
    Lock();
}

void Handler::unlock()
{
    Unlock();
}

void Handler::addTextToExecute(const char *text)
{
    lock();
    textToExecute += " ";
    textToExecute += text;
    unlock();
}


bool Handler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
    rect = CefRect(0, 0, application::getWidth(), application::getHeight());
    return true;
}

void Handler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height)
{
    texture->SetData(0, 0, 0, width, height, buffer);
}

bool Handler::OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request)
{
    std::string initial_url = request->GetURL().ToString().c_str();

    if(initial_url.substr(0,12) == "file:///gui/")
    {
        char cwd[1024];
        std::string file_path, final_url;

        final_url = "file://";

        #ifdef _WINDOWS
            final_url += _getcwd(cwd, 1024);
        #else
            final_url += getcwd(cwd, 1024);
        #endif

        file_path = initial_url.substr(7);

        final_url += file_path;

        request->SetURL(final_url);

        return false;
    }

    #ifdef _WINDOWS
        if(initial_url.substr(0,8) == "file:///"
            && initial_url.substr(9,6) == ":/gui/"
            )
        {
            char cwd[1024];
            std::string file_path, final_url;

            final_url = "file://";
            final_url += _getcwd(cwd, 1024);
            file_path = initial_url.substr(10);

            final_url += file_path;

            request->SetURL(final_url);

            return false;
        }
    #endif


    return false;
}

void Handler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
    static std::string script_text = "if gengine.gui.onPageLoaded then gengine.gui.onPageLoaded() end";
    addTextToExecute(script_text.c_str());
}

}
}
#endif
