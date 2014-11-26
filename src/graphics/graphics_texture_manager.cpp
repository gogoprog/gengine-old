#include "graphics_texture_manager.h"

#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

bool TextureManager::internalCreate(Texture * texture, script::State state)
{
    const char * path = lua_tostring(state, 1);
    return texture->setFromFile(path);
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

void TextureManager::internalInit()
{
    defaultItem = new Texture();
    defaultItem->init();
    defaultItem->setDefault();
}

void TextureManager::internalFinalize()
{
    defaultItem->finalize();
    delete defaultItem;
}

}
}
