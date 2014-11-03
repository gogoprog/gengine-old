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
    fixture(nullptr),
    itIsSensor(false),
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
        b2PolygonShape * shape = new b2PolygonShape();

        Vector2 extent;

        Vector2::fill(state, extent, 3);

        shape->SetAsBox(extent.x * 0.5f, extent.y * 0.5f);

        self.shape = shape;
    }
    else if(!strcmp(key, "radius"))
    {
        b2CircleShape * shape = new b2CircleShape();

        shape->m_radius = lua_tonumber(state, 3);

        self.shape = shape;
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
        else if(!strcmp(type, "kinematic"))
        {
            self.bodyDefinition.type = b2_kinematicBody;
        }
    }
    else if(!strcmp(key, "world"))
    {
        self.worldIndex = lua_tonumber(state, 3);
    }
    else if(!strcmp(key, "density"))
    {
        self.fixtureDefinition.density = lua_tonumber(state, 3);
    }
    else if(!strcmp(key, "restitution"))
    {
        self.fixtureDefinition.restitution = lua_tonumber(state, 3);
    }
    else if(!strcmp(key, "friction"))
    {
        self.fixtureDefinition.friction = lua_tonumber(state, 3);
    }
    else if(!strcmp(key, "linearDamping"))
    {
        self.bodyDefinition.linearDamping = lua_tonumber(state, 3);
    }
    else if(!strcmp(key, "angularDamping"))
    {
        self.bodyDefinition.angularDamping = lua_tonumber(state, 3);
    }
    else if(!strcmp(key, "fixedRotation"))
    {
        self.bodyDefinition.fixedRotation = lua_toboolean(state, 3);
    }
    else if(!strcmp(key, "bullet"))
    {
        self.bodyDefinition.bullet = lua_toboolean(state, 3);
    }
    else if(!strcmp(key, "sensor"))
    {
        self.itIsSensor = lua_toboolean(state, 3);

        if(self.fixture)
        {
            self.fixture->SetSensor(self.itIsSensor);
        }
    }
    else
    {
        geLog("Unknown attribute \"" << key << "\"");
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, init)
{
    SCRIPT_GET_SELF(ComponentPhysic);

    Transform transform;
    fillTransformFromComponent(state, transform);

    self.bodyDefinition.position.Set(transform.position.x, transform.position.y);
    self.body = physics::System::getInstance().getWorld(self.worldIndex).CreateBody(&self.bodyDefinition);

    self.fixtureDefinition.shape = self.shape;

    self.fixture = self.body->CreateFixture(&self.fixtureDefinition);
    self.fixture->SetSensor(self.itIsSensor);

    self.body->SetActive(false);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, insert)
{
    SCRIPT_GET_SELF(ComponentPhysic);

    Transform transform;
    fillTransformFromComponent(state, transform);

    self.body->SetTransform(b2Vec2(transform.position.x, transform.position.y), transform.rotation);

    self.body->SetActive(true);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, update)
{
    SCRIPT_GET_SELF(ComponentPhysic);
    Transform transform;

    switch(self.bodyDefinition.type)
    {
        case b2_dynamicBody:
        {
            b2Vec2 position = self.body->GetPosition();
            float32 angle = self.body->GetAngle();

            transform.position.x = position.x;
            transform.position.y = position.y;
            transform.rotation = angle;

            updateTransformFromComponent(state, transform);
        }
        break;

        case b2_staticBody:
        {

        }
        break;

        case b2_kinematicBody:
        {
            fillTransformFromComponent(state, transform);

            self.body->SetTransform(b2Vec2(transform.position.x, transform.position.y), transform.rotation);
        }
        break;
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentPhysic, remove)
{
    SCRIPT_GET_SELF(ComponentPhysic);

    self.body->SetActive(false);

    return 0;
}

uint
    ComponentPhysic::metaTableRef;

}
}
