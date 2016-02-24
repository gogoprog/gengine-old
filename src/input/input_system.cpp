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

    setMouseVisible(true);
}

void System::finalize()
{
    geDebugLog("input::System::finalize()");
}

void System::update()
{
}

}
}
