#pragma once

#include "input_mouse.h"
#include "primitives.h"
#include "array.h"

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
    void update();

private:
    Array<Mouse>
        mouseTable;
};

}
}
