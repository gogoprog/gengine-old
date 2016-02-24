#include "input_system.h"

#include "core_sdl.h"
#include "core.h"
#include "debug.h"

namespace gengine
{
namespace input
{

void System::init()
{
    geDebugLog("input::System::init()");
    input = & core::getInput();
}

void System::finalize()
{
}

void System::update()
{
}

}
}
