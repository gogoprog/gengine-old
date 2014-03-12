#pragma once

#include "input/mouse.h"
#include "kernel/primitives.h"
#include "kernel/array.h"

namespace gengine
{
namespace input
{

class System
{
public:
    SINGLETON(System);
    const Mouse & getMouse(const int index) const { return mouseTable[index]; }
    void init();
    void updateMouseCoordinates(const int index, const int x, const int y);
    void updateMouseButton(const int index, const int button_index, const Mouse::ButtonState state);

private:
    Array<Mouse> mouseTable;
};

}
}
