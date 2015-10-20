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
        if(setFromSdlSurface(*image))
        {
            SDL_FreeSurface(image);
            return true;
        }

        return false;
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

bool Texture::setFromSdlSurface(const SDL_Surface & surface)
{
    bool pot = true;
    void * data;
    int bpp = surface.format->BytesPerPixel;
    GLenum texture_format, internal_texture_format;

    bpp = surface.format->BytesPerPixel;

    if((surface.w & (surface.w - 1)) || (surface.h & (surface.h - 1)))
    {
        pot = false;
    }

    switch(bpp)
    {
        case 4:
        {
            if(surface.format->Rmask == 0x000000ff)
            {
                texture_format = GL_RGBA;
            }
            else
            {
                texture_format = GL_BGRA;
            }

            internal_texture_format = GL_RGBA;
        }
        break;

        case 3:
        {
            if(surface.format->Rmask == 0x000000ff)
            {
                texture_format = GL_RGB;
            }
            else
            {
                texture_format = GL_BGR;
            }

            internal_texture_format = GL_RGB;
        }
        break;

        case 1:
        {
            texture_format = GL_ALPHA;
            internal_texture_format = GL_ALPHA;
        }
        break;

        default:
        {
            geDebugRawLog("Failed! Unsupported format");

            return false;
        }
        break;
    }

    if(surface.format->palette)
    {
        uint8 * uint8_data = new uint8[surface.w * surface.h * 4];
        data = uint8_data;
        auto & colors = surface.format->palette->colors;

        for(int y=0; y<surface.h; ++y)
        {
            for(int x=0; x<surface.w; ++x)
            {
                uint offset = (y * surface.w + x);
                auto & color = colors[((uint8*)surface.pixels)[y * surface.pitch + x]];

                uint8_data[offset * 4 + 0] = color.r;
                uint8_data[offset * 4 + 1] = color.g;
                uint8_data[offset * 4 + 2] = color.b;
                uint8_data[offset * 4 + 3] = color.a;
            }
        }

        texture_format = GL_RGBA;
        internal_texture_format = GL_RGBA;
    }
    else
    {
        data = surface.pixels;
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

    glTexImage2D(GL_TEXTURE_2D, 0, internal_texture_format, surface.w, surface.h, 0, texture_format, GL_UNSIGNED_BYTE, data);

    width = surface.w;
    height = surface.h;

    if(surface.format->palette)
    {
        delete [](uint8*)data;
    }

    geDebugRawLog("#" << id << " " << width << "x" << height);

    return true;
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
