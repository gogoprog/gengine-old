#pragma once

#include "script.h"
#include "physics_system.h"
#include "physics_world.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentPhysic
{
public:
    ComponentPhysic();

    ENTITY_COMPONENT_DECLARE(ComponentPhysic);

    ENTITY_COMPONENT_METHOD_DECLARE(applyAngularImpulse);
    ENTITY_COMPONENT_METHOD_DECLARE(applyForce);
    ENTITY_COMPONENT_METHOD_DECLARE(applyForceToCenter);
    ENTITY_COMPONENT_METHOD_DECLARE(applyLinearImpulse);
    ENTITY_COMPONENT_METHOD_DECLARE(applyTorque);

protected:
    b2Body
        * body;
    b2Fixture
        * fixture;
    b2BodyDef
        bodyDefinition;
    b2Shape
        * shape;
    b2FixtureDef
        fixtureDefinition;
    bool
        itIsSensor;
    uint
        worldIndex;
};

}
}
