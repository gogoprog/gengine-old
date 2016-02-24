#include "entity_component_physic.h"

#include "physics_system.h"
#include "entity.h"
#include "entity_system.h"
#include "entity_entity.h"
#include "script.h"
#include "script_system.h"
#include "debug.h"
#include <string.h>

namespace gengine
{

using namespace math;

namespace entity
{

ComponentPhysic::ComponentPhysic()
    :
    Component(),
    body(nullptr),
    fixture(nullptr),
    itIsSensor(false),
    worldIndex(0)
{
}

void ComponentPhysic::init()
{
    bodyDefinition.position.Set(-10000, -10000);
    body = physics::System::getInstance().getWorld(worldIndex).getBox2dWorld().CreateBody(&bodyDefinition);

    fixtureDefinition.shape = shape;

    fixture = body->CreateFixture(&fixtureDefinition);
    fixture->SetSensor(itIsSensor);

    body->SetActive(false);

    fixture->SetUserData(reinterpret_cast<void*>(&*entity));
}

void ComponentPhysic::insert()
{
    /*Transform & transform = entity->transform;

    body->SetTransform(b2Vec2(transform.position.x, transform.position.y), transform.rotation);

    body->SetActive(true);*/
}

void ComponentPhysic::update(const float /*dt*/)
{
    /*Transform & transform = entity->transform;

    switch(bodyDefinition.type)
    {
        case b2_dynamicBody:
        {
            b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();

            transform.position.x = position.x;
            transform.position.y = position.y;
            transform.rotation = angle;

            script::update(script::System::getInstance().getState(), transform);
        }
        break;

        case b2_staticBody:
        {
        }
        break;

        case b2_kinematicBody:
        {
            body->SetTransform(b2Vec2(transform.position.x, transform.position.y), transform.rotation);
        }
        break;
    }*/
}

void ComponentPhysic::remove()
{
    body->SetActive(false);
}

ENTITY_COMPONENT_IMPLEMENT(ComponentPhysic)
{
    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        applyAngularImpulse,
        {
            /*SCRIPT_GET_SELF(ComponentPhysic);
            float impulse = lua_tonumber(state, 2);

            self.body->ApplyAngularImpulse(impulse);*/
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        applyForce,
        {
            /*SCRIPT_GET_SELF(ComponentPhysic);
            Vector2 force;
            Vector2 point;

            script::get(state, force, 2);
            script::get(state, point, 3);

            self.body->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(point.x, point.y));*/
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        applyForceToCenter,
        {
            /*SCRIPT_GET_SELF(ComponentPhysic);
            Vector2 force;

            script::get(state, force, 2);

            self.body->ApplyForceToCenter(b2Vec2(force.x, force.y));*/
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        applyLinearImpulse,
        {
            /*SCRIPT_GET_SELF(ComponentPhysic);
            Vector2 impulse;
            Vector2 point;

            script::get(state, impulse, 2);
            script::get(state, point, 3);

            self.body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), b2Vec2(point.x, point.y));*/
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        applyTorque,
        {
            /*SCRIPT_GET_SELF(ComponentPhysic);
            float torque = lua_tonumber(state, 2);

            self.body->ApplyTorque(torque);*/
            return 0;
        }
        );
}

ENTITY_COMPONENT_SETTERS(ComponentPhysic)
{
    /*ENTITY_COMPONENT_SETTER_FIRST(extent)
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
    ENTITY_COMPONENT_SETTER_END()*/
}
ENTITY_COMPONENT_END()

}
}
