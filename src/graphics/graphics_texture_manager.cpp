#include "graphics_texture_manager.h"

#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

bool TextureManager::internalCreate(Texture * texture, const char * arg)
{
    return texture->setFromFile(arg);
}

void TextureManager::internalGetName(char * result, const char * file_path)
{
    const char * begin, * end;
    uint length;

    if(!(begin = strrchr(file_path,'/')))
    {
        begin = file_path;
    }
    else
    {
        ++begin;
    }

    if(!(end = strrchr(begin,'.')))
    {
        end = begin + strlen(begin);
    }

    length = end - begin;

    strncpy(result, begin, length);
    result[length] = 0;
}

}
}
