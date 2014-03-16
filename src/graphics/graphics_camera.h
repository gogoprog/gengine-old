#pragma once

#include "primitives.h"
#include "vector2.h"
#include "matrix3.h"

namespace gengine
{
namespace graphics
{

class Camera
{

public:
    Camera();
    void init();
    void finalize();
    void update();

    const Matrix3 & getProjectionMatrix() { return projectionMatrix; }
    const Vector2 & getPosition() { return position; }
    const Vector2 & getExtent() { return extent; }

    void setPosition(const Vector2 & _position);
    void setExtent(const Vector2 & _extent);

private:
    Matrix3 projectionMatrix;
    Vector2 position;
    Vector2 extent;
    bool dirty;
};

}
}
