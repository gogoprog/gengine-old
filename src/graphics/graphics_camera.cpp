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
    dirtyProjection(true),
    dirtyRatio(true)
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
    if(dirtyProjection)
    {
        dirtyProjection = false;

        projectionMatrix.initProjection(extent, position);
    }

    if(dirtyRatio)
    {
        dirtyRatio = false;

        screenRatio.x = application::getWidth() / extent.x;
        screenRatio.y = application::getHeight() / extent.y;
    }
}

void Camera::setPosition(const Vector2 & _position)
{
    position = _position;
    dirtyProjection = true;
}

void Camera::setExtent(const Vector2 & _extent)
{
    extent = _extent;
    dirtyProjection = true;
    dirtyRatio = true;
}

void Camera::getWorldPosition(Vector2 & result, const Vector2 & position) const
{
    result.x = position.x;
    result.y = application::getHeight() - position.y;

    result /= screenRatio;

    result += getPosition();

    result -= getExtent() * 0.5f;
}

}
}
