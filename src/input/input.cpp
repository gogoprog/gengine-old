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

    system.getKeyboard().luaRegister(state);


    lua_newtable(state);

    for(uint i=0; i<System::JOYPAD_COUNT; ++i)
    {
        system.getJoypad(i).luaRegister(state);
    }

    lua_setfield(state, -2, "joypads");

    SCRIPT_DO(
        return function(t, i) return t.joypads[i] end
        );

    lua_setfield(state, -2, "getJoypad");

    lua_setfield(state, -2, "input");
}

}
}
