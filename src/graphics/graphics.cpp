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

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        setClearColor,
        {
            core::getRenderer().GetDefaultZone()->SetFogColor(*script::get<Urho3D::Color>(state, 1));
            return 0;
        });

    lua_setfield(state, -2, "graphics");
}

}
}
