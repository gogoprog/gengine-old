#include "graphics_sprite_manager.h"

#include "debug.h"
#include "core.h"

namespace gengine
{
namespace graphics
{

void SpriteManager::simplifyName(char *result, const char *file_path)
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

Urho3D::Sprite2D * SpriteManager::internalCreate(script::State state, const int parameter_position)
{
    const char * path = lua_tostring(state, parameter_position);

    return core::getResourceCache().GetResource<Urho3D::Sprite2D>(path);
}

void SpriteManager::internalGetName(char * result, const char * file_path)
{
    simplifyName(result, file_path);
}

void SpriteManager::internalInit()
{
    /*defaultItem = new Texture();
    defaultItem->init();
    defaultItem->setDefault();*/
}

void SpriteManager::internalFinalize()
{
    /*defaultItem->finalize();
    delete defaultItem;*/
}

}
}
