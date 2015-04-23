#include "graphics_texture_manager.h"

#include "debug.h"
#include <cstring>
#include <dirent.h> 

namespace gengine
{
namespace graphics
{

SCRIPT_CLASS_FUNCTION(TextureManager, createFromDirectory)
{
    const char * path = lua_tostring(state, 1);
    DIR * directory;
    dirent * result;

    directory = opendir(path);

    if(directory)
    {
        while((result = readdir(directory)))
        {
            std::string str_name = result->d_name;
            size_t length = str_name.length();

            if(length > 4)
            {
                std::string extension = str_name.substr(length - 4);

                if(extension == ".png")
                {
                    std::string final_path = path;
                    final_path += "/";
                    final_path += str_name;

                    lua_pushstring(state, final_path.c_str());
                    getInstance().createItem(state, -1);
                    lua_pop(state, 1);
                }
            }
        }

        closedir(directory);
    }

    return 0;
}

bool TextureManager::internalCreate(Texture * texture, script::State state, const int parameter_position)
{
    const char * path = lua_tostring(state, parameter_position);
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

void TextureManager::internalLuaRegister(script::State state)
{
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(TextureManager, createFromDirectory);
}

}
}
