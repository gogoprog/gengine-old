#pragma once

#include "primitives.h"
#include "vector2.h"
#include "stack.h"
#include "array.h"
#include "graphics_uniform.h"

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
    void render();
    void addSprite(Sprite & sprite);

private:
    Stack<Camera*>
        cameraStack;
    Array<Sprite*>
        spriteTable;
    Uniform
        projectionMatrixUniform,
        transformMatrixUniform,
        samplerUniform,
        colorUniform;
};

}
}
