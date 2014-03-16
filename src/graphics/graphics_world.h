#pragma once

#include "primitives.h"
#include "vector2.h"
#include "stack.h"
#include "array.h"

namespace gengine
{
namespace graphics
{

class Camera;
class Sprite;

class World
{
friend class System;

public:
    World();
    void init();
    void finalize();
    void update();

private:
    Stack<Camera*> cameraStack;
    Array<Sprite*> spriteTable;
};

}
}
