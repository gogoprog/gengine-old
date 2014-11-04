#pragma once

#include "script.h"
#include "physics_system.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentPhysic
{
public:
    ComponentPhysic();

    ENTITY_COMPONENT_DECLARE();

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
