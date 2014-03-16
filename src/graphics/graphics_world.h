#pragma once

#include "primitives.h"
#include "vector2.h"
#include "stack.h"

namespace gengine
{
namespace graphics
{

class Camera;

class World
{
friend class System;

public:
    World();
    void init();
    void finalize();

private:
    Stack<const Camera*> cameraStack;
};

}
}
