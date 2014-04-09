#include "graphics_animation.h"

#include "core_sdl.h"
#include "graphics_opengl.h"
#include "debug.h"

namespace gengine
{
namespace graphics
{

Animation::Animation()
{
}

void Animation::init()
{
}

void Animation::finalize()
{
}

bool Animation::set(lua_State * state)
{
    const graphics::Atlas * atlas;

    lua_getfield(state, 2, "atlas");
    atlas = static_cast<graphics::Atlas *>(lua_touserdata(state, -1));
    lua_pop(state, 1);

    lua_getfield(state, 2, "frames");
    lua_pushnil(state);
    while(lua_next(state, -2) != 0)
    {
        frameTable.add(AnimationFrame(atlas, lua_tonumber(state, -1)));
        lua_pop(state, 1);
    }
    lua_pop(state, 1);

    (void)atlas;

    return false;
}

}
}
