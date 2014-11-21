#include "kernel.h"

#include "script.h"
#include "vector2.h"
#include "vector4.h"

#ifndef EMSCRIPTEN
    #include <signal.h>
#else
    #include <emscripten.h>
#endif

namespace gengine
{
namespace kernel
{

void breakExecution()
{
    #ifndef EMSCRIPTEN
        #ifdef _LINUX
            raise(SIGTRAP);
        #endif
    #else
        emscripten_debugger();
    #endif
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    Vector2::luaRegister(state);
    Vector4::luaRegister(state);

    lua_setfield(state, -2, "math");
}

}
}
