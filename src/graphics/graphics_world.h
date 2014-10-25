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
friend class Renderer;

public:
    World();
    void init();
    void finalize();
    void update();
    void addSprite(Sprite & sprite);
    void removeSprite(Sprite & sprite);
    void pushCamera(Camera & camera);
    void popCamera();
    const Camera & getCurrentCamera() const;

private:
    static bool compare(Sprite *a, Sprite *b);

    Stack<const Camera*>
        cameraStack;
    Array<Sprite*>
        spriteTable;
    Uniform
        projectionMatrixUniform,
        transformMatrixUniform,
        samplerUniform,
        colorUniform,
        uvScaleUniform,
        uvOffsetUniform;
};

}
}
