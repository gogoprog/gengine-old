#include "input.h"

#include "script.h"

namespace gengine
{
namespace input
{

SCRIPT_REGISTERER()
{
    lua_newtable(state);
    lua_setglobal(state,"input");
}

}
}
