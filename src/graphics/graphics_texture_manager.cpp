#include "graphics_texture_manager.h"

#include "debug.h"

namespace gengine
{
namespace graphics
{

SCRIPT_CLASS_REGISTERER(TextureManager)
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(TextureManager, load);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(TextureManager, get);
}

SCRIPT_CLASS_FUNCTION(TextureManager, load)
{
    const char * name = lua_tostring(state, 1);
    Texture * texture = new Texture();

    texture->setFromFile(name);

    getInstance().textureMap.add(texture, name);

    return 0;
}

SCRIPT_CLASS_FUNCTION(TextureManager, get)
{
    return 1;
}

}
}
