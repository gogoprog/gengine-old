#pragma once

#include "script.h"
#include "entity_macros.h"
#include "entity_component.h"
#include "entity_component_generic.h"
#include <Urho3D/Urho2D/RigidBody2D.h>

namespace gengine
{
namespace entity
{

class ComponentRigidBody2D : public ComponentGeneric<Urho3D::RigidBody2D>
{
public:
    ComponentRigidBody2D() = default;

    virtual void onPropertySet(const char *name)
    {
        itDrivesTransform = (urhoComponent->GetBodyType() == Urho3D::BT_DYNAMIC);
    }

    static SCRIPT_FUNCTION(create)
    {
        return System::getInstance().createComponent<ComponentRigidBody2D>(state);
    }
};

}
}
