#include "graphics_texture.h"

#include "core_sdl.h"
#include "graphics_opengl.h"
#include "debug.h"

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

        if((image->w & (image->w - 1)) || (image->h & (image->h - 1)))
        {
            SDL_FreeSurface (image);

            geDebugRawLog("Failed! Non-power-of-2. " << image->w << "x" << image->h);

            return false;
        }

        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

        width = image->w;
        height = image->h;
        SDL_FreeSurface (image);

        geDebugRawLog("#" << id << " " << width << "x" << height);

        return true;
    }
    else
    {
        geDebugRawLog("Failed! " << IMG_GetError());

        return false;
    }
}

}
}
