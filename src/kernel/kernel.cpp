#include "kernel.h"

#include "script.h"
#include "vector2.h"
#include "vector4.h"
#include "maths.h"

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
        #ifndef NDEBUG
            emscripten_debugger();
        #endif
    #endif
}

SCRIPT_REGISTERER()
{
    math::luaRegister(state);
}

}
}
