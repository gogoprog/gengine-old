#pragma once

#include "script.h"
#include "entity_macros.h"
#include "entity_component.h"
#include "entity_component_generic.h"
#include <Urho3D/Graphics/Camera.h>

namespace gengine
{
namespace entity
{

class ComponentCamera : public ComponentGeneric<Urho3D::Camera>
{
public:
    ComponentCamera() = default;

    virtual void insert() override;
    virtual void remove() override;

    static SCRIPT_FUNCTION(create)
    {
        return System::getInstance().createComponent<ComponentCamera>(state);
    }
};

}
}
