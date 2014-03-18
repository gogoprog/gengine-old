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

    system.getMouse(0).luaRegister(state);
    lua_setfield(state, -2, "mouse");

    lua_setglobal(state, "input");
}

}
}
