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

    const Matrix3 & getProjectionMatrix() const { return projectionMatrix; }
    const Vector2 & getPosition() const { return position; }
    Vector2 & getPosition() { return position; }
    const Vector2 & getExtent() const { return extent; }
    Vector2 & getExtent() { return extent; }

    void setPosition(const Vector2 & _position);
    void setExtent(const Vector2 & _extent);

    void getWorldPosition(Vector2 & result, const Vector2 & position) const;

private:
    Matrix3
        projectionMatrix;
    Vector2
        position,
        extent,
        screenRatio;
    bool
        dirtyProjection,
        dirtyRatio;
};

}
}
