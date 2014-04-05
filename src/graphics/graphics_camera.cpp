#include "graphics_camera.h"

#include "graphics_opengl.h"
#include "debug.h"
#include "application.h"

namespace gengine
{
namespace graphics
{

Camera::Camera()
    :
    position(Vector2::zero),
    dirty(true)
{
}

void Camera::init()
{

}

void Camera::finalize()
{

}

void Camera::update()
{
    if(dirty)
    {
        dirty = false;

        projectionMatrix.initProjection(extent, position);

        screenRatio.x = application::getWidth() / extent.x;
        screenRatio.y = application::getHeight() / extent.y;
    }
}

void Camera::setPosition(const Vector2 & _position)
{
    position = _position;
    dirty = true;
}

void Camera::setExtent(const Vector2 & _extent)
{
    extent = _extent;
    dirty = true;
}

void Camera::getWorldPosition(Vector2 & result, const Vector2 & position) const
{
    Vector2 ratio;

    result.x = position.x;
    result.y = application::getHeight() - position.y;

    result /= screenRatio;

    result += getPosition();

    result -= getExtent() * 0.5f;
}


}
}
