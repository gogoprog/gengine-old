#include "graphics_font_manager.h"

#include "debug.h"
#include <cstring>
#include "core_sdl.h"

namespace gengine
{
namespace graphics
{

bool FontManager::internalCreate(Font * font, script::State state, const int parameter_position)
{
    const char * path = lua_tostring(state, parameter_position);
    int size = int(lua_tonumber(state, parameter_position + 1));
    return font->setFromFile(path, size);
}

void FontManager::internalGetName(char * result, const char * name)
{
    strcpy(result, name);
}

void FontManager::internalInit()
{
    TTF_Init();
}

void FontManager::internalFinalize()
{
    TTF_Quit();
}

}
}
