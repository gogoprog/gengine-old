#include "kernel.h"

#include "script.h"
#include "vector2.h"
#include "vector4.h"

namespace gengine
{
namespace kernel
{

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    Vector2::luaRegister(state);
    Vector4::luaRegister(state);

    lua_setfield(state, -2, "math");
}

}
}
