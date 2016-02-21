#pragma once

#include "script.h"
#include "graphics_camera.h"
#include "entity_macros.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentCamera : public Component
{
public:
    ComponentCamera();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentCamera);

private:
    graphics::Camera
        camera;
    uint
        worldIndex;
};

}
}
