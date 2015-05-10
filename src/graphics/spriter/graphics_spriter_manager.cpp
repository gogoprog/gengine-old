#include "graphics_spriter_manager.h"

#include "debug.h"
#include "core_json.h"
#include <cstring>
#include <iostream>
#include <fstream> 

namespace gengine
{
namespace graphics
{

SCRIPT_CLASS_FUNCTION(SpriterManager, loadFile)
{
    const char * path = lua_tostring(state, 1);

    std::filebuf fb;

    if (fb.open (path, std::ios::in))
    {
        core::Json json;
        std::istream istream(&fb);

        json.parse(istream);
    }

    return 0;
}

bool SpriterManager::internalCreate(SpriterAnimation * animation, script::State state, const int parameter_position)
{
    return false;
}

void SpriterManager::internalGetName(char * result, const char * arg)
{
    strcpy(result, arg);
}

void SpriterManager::internalLuaRegister(script::State state)
{
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(SpriterManager, loadFile);
}

}
}
