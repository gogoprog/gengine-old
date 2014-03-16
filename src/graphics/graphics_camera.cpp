#include "graphics_camera.h"

#include "graphics_opengl.h"
#include "debug.h"

namespace gengine
{
namespace graphics
{

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

        projectionMatrix.init();
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

}
}
