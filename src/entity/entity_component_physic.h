#pragma once

#include "script.h"
#include "physics_system.h"

namespace gengine
{
namespace entity
{

class ComponentPhysic
{
public:
    ComponentPhysic();

    static SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(insert);
    static SCRIPT_FUNCTION(update);
    static SCRIPT_FUNCTION(remove);

    static uint
        metaTableRef;

protected:
    b2Body
        * body;
    b2Fixture
        * fixture;
    b2BodyDef
        bodyDefinition;
    b2PolygonShape
        shape;
    b2FixtureDef
        fixtureDefinition;
    bool
        itIsSensor;
    uint
        worldIndex;
};

}
}
