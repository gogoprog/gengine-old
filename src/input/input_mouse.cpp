#include "input_mouse.h"

namespace gengine
{
namespace input
{


bool Mouse::isDown(const int index) const
{
    return buttonStateTable[index] == DOWN;
}

bool Mouse::isUp(const int index) const
{
    return buttonStateTable[index] == UP;
}

}
}
