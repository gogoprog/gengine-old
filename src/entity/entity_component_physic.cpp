#include "entity_component_physic.h"

#include "physics_system.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{
namespace entity
{

ComponentPhysic::ComponentPhysic()
    :
    body(nullptr),
    worldIndex(0)
{
}

SCRIPT_CLASS_REGISTERER(ComponentPhysic)
{
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, create)
{
    return System::getInstance().createComponent<ComponentPhysic>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, newIndex)
{
    SCRIPT_GET_SELF(ComponentPhysic);
    const char * key = lua_tostring(state, 2);

    if(!strcmp(key, "extent"))
    {
        Vector2 extent;

        Vector2::fill(state, extent, 3);

        self.shape.SetAsBox(extent.x, extent.y);
    }
    else if(!strcmp(key, "type"))
    {
        const char * type = lua_tostring(state, 3);

        if(!strcmp(type, "dynamic"))
        {
            self.bodyDefinition.type = b2_dynamicBody;
        }
        else if(!strcmp(type, "static"))
        {
            self.bodyDefinition.type = b2_staticBody;
        }
    }
    else if(!strcmp(key, "world"))
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    else
    {
        geLog("Unknown attribute \"" << key << "\"");
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, init)
{
    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, insert)
{
    SCRIPT_GET_SELF(ComponentPhysic);

    Transform transform;
    fillTransformFromComponent(state, transform);

    self.bodyDefinition.position.Set(transform.position.x, transform.position.y);

    self.body = physics::System::getInstance().getWorld(self.worldIndex).CreateBody(&self.bodyDefinition);

    self.fixtureDefinition.shape = &self.shape;
    self.fixtureDefinition.density = 1.0f;
    self.fixtureDefinition.friction = 0.3f;

    self.body->CreateFixture(&self.fixtureDefinition);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, update)
{
    SCRIPT_GET_SELF(ComponentPhysic);
    Transform transform;

    b2Vec2 position = self.body->GetPosition();
    float32 angle = self.body->GetAngle();

    transform.position.x = position.x;
    transform.position.y = position.y;
    transform.rotation = angle;

    updateTransformFromComponent(state, transform);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, remove)
{
    // :todo:

    return 0;
}

uint
    ComponentPhysic::metaTableRef;

}
}
