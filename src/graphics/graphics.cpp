#include "graphics.h"

#include "script.h"
#include "application.h"
#include "graphics_spriter_manager.h"
#include "graphics_sprite_manager.h"
#include "graphics_spine_manager.h"
#include "vector4.h"
#include "core.h"
#include <Urho3D/Graphics/Zone.h>

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

    SpriteManager::luaRegister(state);
    lua_setfield(state, -2, "sprite");

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        setClearColor,
        {
            core::getRenderer().GetDefaultZone()->SetFogColor(
                Urho3D::Color(
                    lua_tonumber(state, 1),
                    lua_tonumber(state, 2),
                    lua_tonumber(state, 3)
                )
            );
            return 0;
        });

    lua_setfield(state, -2, "graphics");
}

}
}
