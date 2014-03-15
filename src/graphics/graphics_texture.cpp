#include "graphics_texture.h"

#include "core_sdl.h"
#include "graphics_opengl.h"

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

void Texture::setFromFile(const char * filename)
{
    SDL_Surface *image = IMG_Load(filename);

    if(image)
    {
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, image->pixels);

        width = image->w;
        height = image->h;
        SDL_FreeSurface (image);
    }
}

}
}
