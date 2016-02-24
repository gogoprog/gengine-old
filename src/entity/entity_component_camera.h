#pragma once

#include "script.h"
#include "entity_macros.h"
#include "entity_component.h"
#include <Urho3D/Graphics/Camera.h>

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
    Urho3D::SharedPtr<Urho3D::Camera>
        camera;
};

}
}
