#include "kernel.h"

#include "script.h"
#include "vector2.h"

namespace gengine
{
namespace kernel
{

SCRIPT_REGISTERER()
{
    Vector2::luaRegister(state);
}

}
}
