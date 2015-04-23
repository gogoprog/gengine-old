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
class Object;

class World
{
friend class System;
friend class Renderer;

public:
    World();
    void init();
    void finalize();
    void update();
    void addObject(Object & object);
    void removeObject(Object & object);
    void pushCamera(Camera & camera);
    void popCamera();
    const Camera & getCurrentCamera() const;

private:
    static bool compare(Object *a, Object *b);

    Stack<const Camera*>
        cameraStack;
    Array<Object*>
        objectTable;
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
