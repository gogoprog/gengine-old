#ifndef EMSCRIPTEN
#include "gui_cef_handler.h"

#include "include/cef_client.h"
#include "application.h"
#include "debug.h"
#include "core.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "script_system.h"

#ifdef _WINDOWS
    #include <direct.h>
#else
    #include "unistd.h"
#endif

namespace gengine
{
namespace gui
{

const char vertex_shader_source[] = GL_GLSL(
    attribute vec2 position;
    attribute vec2 texCoords;
    varying highp vec2 v_texCoords;

    void main()
    {
        v_texCoords = texCoords;
        gl_Position = vec4(position * 2.0,1,1);
    }
);

const char fragment_shader_source[] = GL_GLSL(
    varying highp vec2 v_texCoords;
    uniform sampler2D tex0;

    void main()
    {
        gl_FragColor = texture2D(tex0, v_texCoords).rgba;
    }
);

void Handler::init()
{
    uint width = application::getWidth();
    uint height = application::getHeight();

    glGenBuffers(1, &pboId);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboId);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    texture.init();

    glBindTexture(GL_TEXTURE_2D, texture.getId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    vertexShader.init(GL_VERTEX_SHADER);
    vertexShader.compile(vertex_shader_source);

    fragmentShader.init(GL_FRAGMENT_SHADER);
    fragmentShader.compile(fragment_shader_source);

    program.init();
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);
    program.link();

    samplerUniform.init(program, "tex0");

    GL_CHECK();
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

void Handler::render()
{
    graphics::System & system = graphics::System::getInstance();

    program.use();

    system.getVertexBufferQuad().apply();

    samplerUniform.apply(texture);

    system.getIndexBufferQuad().draw(6);

    glUseProgram(0);
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
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboId);

    void * memory = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
    memcpy(memory, buffer, width * height * 4);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

    glBindTexture(GL_TEXTURE_2D, texture.getId());

    /*for(const CefRect & rect : dirtyRects)
    {
        glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.width, rect.height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    }*/

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
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
    }

    return false;
}

}
}
#endif
