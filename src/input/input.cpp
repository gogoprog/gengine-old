#include "input.h"

#include "input_system.h"
#include "script.h"

namespace gengine
{
namespace input
{

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isKeyDown,
        {
            lua_pushboolean(state, System::getInstance().isKeyDown(int(lua_tonumber(state, 1))));
            return 1;
        }
    );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isKeyUp,
        {
            lua_pushboolean(state, System::getInstance().isKeyUp(int(lua_tonumber(state, 1))));
            return 1;
        }
    );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isKeyJustDown,
        {
            lua_pushboolean(state, System::getInstance().isKeyJustDown(int(lua_tonumber(state, 1))));
            return 1;
        }
    );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isMouseButtonDown,
        {
            lua_pushboolean(state, System::getInstance().isMouseButtonDown(int(lua_tonumber(state, 1))));
            return 1;
        }
    );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isMouseButtonUp,
        {
            lua_pushboolean(state, System::getInstance().isMouseButtonUp(int(lua_tonumber(state, 1))));
            return 1;
        }
    );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isMouseButtonJustDown,
        {
            lua_pushboolean(state, System::getInstance().isMouseButtonJustDown(int(lua_tonumber(state, 1))));
            return 1;
        }
    );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        setMouseVisible,
        {
            System::getInstance().isMouseButtonJustDown(lua_toboolean(state, 1));
            return 0;
        }
    );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        getMousePosition,
        {
            script::push(state, System::getInstance().getMousePosition());
            return 1;
        }
    );

    lua_setfield(state, -2, "input");
}

}
}
