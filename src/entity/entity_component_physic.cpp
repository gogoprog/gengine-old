#include "entity_component_physic.h"

#include "physics_system.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{

using namespace math;

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

ENTITY_COMPONENT_IMPLEMENT(ComponentPhysic)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(applyAngularImpulse);
    ENTITY_COMPONENT_PUSH_FUNCTION(applyForce);
    ENTITY_COMPONENT_PUSH_FUNCTION(applyForceToCenter);
    ENTITY_COMPONENT_PUSH_FUNCTION(applyLinearImpulse);
    ENTITY_COMPONENT_PUSH_FUNCTION(applyTorque);
}

ENTITY_COMPONENT_SETTERS(ComponentPhysic)
{
    ENTITY_COMPONENT_SETTER_FIRST(extent)
    {
        b2PolygonShape * shape = new b2PolygonShape();

        Vector2 extent;

        script::get(state, extent, 3);

        shape->SetAsBox(extent.x * 0.5f, extent.y * 0.5f);

        self.shape = shape;
    }
    ENTITY_COMPONENT_SETTER(radius)
    {
        b2CircleShape * shape = new b2CircleShape();

        shape->m_radius = lua_tonumber(state, 3);

        self.shape = shape;
    }
    ENTITY_COMPONENT_SETTER(type)
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
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(density)
    {
        self.fixtureDefinition.density = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(restitution)
    {
        self.fixtureDefinition.restitution = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(friction)
    {
        self.fixtureDefinition.friction = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(linearDamping)
    {
        self.bodyDefinition.linearDamping = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(angularDamping)
    {
        self.bodyDefinition.angularDamping = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(fixedRotation)
    {
        self.bodyDefinition.fixedRotation = lua_toboolean(state, 3);
    }
    ENTITY_COMPONENT_SETTER(bullet)
    {
        self.bodyDefinition.bullet = lua_toboolean(state, 3);
    }
    ENTITY_COMPONENT_SETTER(sensor)
    {
        self.itIsSensor = lua_toboolean(state, 3);

        if(self.fixture)
        {
            self.fixture->SetSensor(self.itIsSensor);
        }
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, init)
{
    Transform transform;
    fillTransformFromComponent(state, transform);

    self.bodyDefinition.position.Set(transform.position.x, transform.position.y);
    self.body = physics::System::getInstance().getWorld(self.worldIndex).getBox2dWorld().CreateBody(&self.bodyDefinition);

    self.fixtureDefinition.shape = self.shape;

    self.fixture = self.body->CreateFixture(&self.fixtureDefinition);
    self.fixture->SetSensor(self.itIsSensor);

    self.body->SetActive(false);

    lua_getfield(state, 1, "entity");
    lua_getfield(state, -1, "_ref");
    int ref = lua_tonumber(state, -1);
    self.fixture->SetUserData(reinterpret_cast<void *>(ref));
    lua_pop(state, 2);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, insert)
{
    Transform transform;
    fillTransformFromComponent(state, transform);

    self.body->SetTransform(b2Vec2(transform.position.x, transform.position.y), transform.rotation);

    self.body->SetActive(true);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, update)
{
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
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, remove)
{
    self.body->SetActive(false);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, applyAngularImpulse)
{
    float impulse = lua_tonumber(state, 2);

    self.body->ApplyAngularImpulse(impulse);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, applyForce)
{
    Vector2 force, point;

    script::get(state, force, 2);
    script::get(state, point, 3);

    self.body->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(point.x, point.y));
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, applyForceToCenter)
{
    Vector2 force;

    script::get(state, force, 2);

    self.body->ApplyForceToCenter(b2Vec2(force.x, force.y));
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, applyLinearImpulse)
{
    Vector2 impulse, point;

    script::get(state, impulse, 2);
    script::get(state, point, 3);

    self.body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), b2Vec2(point.x, point.y));
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentPhysic, applyTorque)
{
    float torque = lua_tonumber(state, 2);

    self.body->ApplyTorque(torque);
}
ENTITY_COMPONENT_END()

}
}
