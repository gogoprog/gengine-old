#include "graphics_texture_manager.h"

#include "debug.h"

namespace gengine
{
namespace graphics
{

void TextureManager::simplifyName(char *result, const char *file_path)
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

bool TextureManager::internalCreate(Texture * texture, script::State state, const int parameter_position)
{
    const char * path = lua_tostring(state, parameter_position);
    return texture->setFromFile(path);
}

void TextureManager::internalGetName(char * result, const char * file_path)
{
    simplifyName(result, file_path);
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
