#include "entity.h"

#include "entity_system.h"
#include "script.h"

namespace gengine
{
namespace entity
{

SCRIPT_REGISTERER()
{
    System::getInstance().luaRegister(state);
}

}
}
