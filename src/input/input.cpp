#include "input.h"

#include "input_system.h"
#include "script.h"

namespace gengine
{
namespace input
{

SCRIPT_REGISTERER()
{
    System & system = System::getInstance();

    lua_newtable(state);

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isKeyDown,
        {
            lua_pushboolean(state, System::getInstance().isKeyDown(int(lua_tonumber(state, 1))));
            return 1;
        }
    );

    lua_setfield(state, -2, "input");
}

}
}
