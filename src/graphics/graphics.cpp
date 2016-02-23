#include "graphics.h"

#include "script.h"
#include "application.h"
#include "graphics_spriter_manager.h"
#include "graphics_spine_manager.h"
#include "vector4.h"

namespace gengine
{
namespace graphics
{

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SpriterManager::luaRegister(state);
    lua_setfield(state, -2, "spriter");

    SpineManager::luaRegister(state);
    lua_setfield(state, -2, "spine");

    lua_setfield(state, -2, "graphics");
}

}
}
