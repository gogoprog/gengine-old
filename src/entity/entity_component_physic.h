#pragma once

#include "script.h"
#include "physics_system.h"
#include "physics_world.h"
#include "entity_macros.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentPhysic : public Component
{
public:
    ComponentPhysic();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentPhysic);

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
