#pragma once

#include "primitives.h"
#include "array.h"
#include "map.h"
#include "core.h"

namespace gengine
{
namespace input
{

class System
{
public:
    SINGLETON(System);

    void init();
    void finalize();
    void update();

    inline bool isKeyUp(const int key) const
    {
        return !input->GetScancodeDown(key);
    }

    inline bool isKeyDown(const int key) const
    {
        return input->GetScancodeDown(key);
    }

    inline bool isKeyJustDown(const int key) const
    {
        return input->GetScancodePress(key);
    }

private:
    Urho3D::Input
        *input;
};

}
}
