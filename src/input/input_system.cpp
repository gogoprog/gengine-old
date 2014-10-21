#include "input_system.h"

#include "core_sdl.h"
#include "debug.h"

namespace gengine
{
namespace input
{

void System::init()
{
    geDebugLog("input::System::init()");

    mouseTable.add(Mouse());
}

void System::updateMouseCoordinates(const int index, const int x, const int y)
{
    Mouse & mouse = mouseTable[index];
    mouse.x = x;
    mouse.y = y;
}

void System::updateMouseButton(const int index, const int button_index, const Mouse::ButtonState state)
{
    Mouse & mouse = mouseTable[index];
    mouse.buttonStateTable[button_index] = state;
}

void System::update()
{
    for(Mouse & mouse : mouseTable)
    {
        for(int i=0; i<Mouse::BUTTON_COUNT; ++i)
        {
            mouse.previousButtonStateTable[i] = mouse.buttonStateTable[i];
        }
    }
}

}
}
