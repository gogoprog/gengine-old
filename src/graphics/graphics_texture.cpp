#include "graphics_texture.h"

#include "core_sdl.h"
#include "graphics_opengl.h"
#include "debug.h"
#include "graphics_texture_manager.h"

namespace gengine
{
namespace graphics
{

Texture::Texture()
    :
    id(GL_NULL_ID)
{
}

void Texture::init()
{
    glGenTextures(1, &id);
}

void Texture::finalize()
{
    glDeleteTextures(1, &id);
}

bool Texture::setFromFile(const char * filename)
{
    geDebugLogN("graphics::Texture::setFromFile \"" << filename << "\" ... ");

    SDL_Surface *image = IMG_Load(filename);

    if(image)
    {
        bool pot = true;

        if((image->w & (image->w - 1)) || (image->h & (image->h - 1)))
        {
            geLog("Warning! Non-power-of-2: \"" << filename << "\" " << image->w << "x" << image->h);
            pot = false;
        }

        int bpp = image->format->BytesPerPixel;
        GLenum texture_format;

        if(bpp == 4)
        {
            if(image->format->Rmask == 0x000000ff)
            {
                texture_format = GL_RGBA;
            }
            else
            {
                texture_format = GL_BGRA;
            }
        }
        else if(bpp == 3)
        {
            if(image->format->Rmask == 0x000000ff)
            {
                texture_format = GL_RGB;
            }
            else
            {
                texture_format = GL_BGR;
            }
        }
        else
        {
            SDL_FreeSurface(image);

            geDebugRawLog("Failed! Unsupported format");

            return false;
        }

        glBindTexture(GL_TEXTURE_2D, id);

        if(pot)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, texture_format, image->w, image->h, 0, texture_format, GL_UNSIGNED_BYTE, image->pixels);

        width = image->w;
        height = image->h;
        SDL_FreeSurface (image);

        geDebugRawLog("#" << id << " " << width << "x" << height);

        return true;
    }
    else
    {
        geLog("Failed to load image \"" << filename << "\" (" << IMG_GetError() << ")");

        return false;
    }
}

void Texture::setDefault()
{
    float pixels[] = {
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f
    };

    width = 2;
    height = 2;

    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
}

void Texture::setWhite()
{
    float pixels[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    width = 2;
    height = 2;

    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
}

}
}
