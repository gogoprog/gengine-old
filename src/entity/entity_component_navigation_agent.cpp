#include "entity_component_navigation_agent.h"

#include "navigation_system.h"
#include "navigation_world.h"
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

ComponentNavigationAgent::ComponentNavigationAgent()
    :
    agent(nullptr),
    worldIndex(0),
    radius(10.0f),
    speed(100.0f)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentNavigationAgent)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(moveTo);
}

ENTITY_COMPONENT_SETTERS(ComponentNavigationAgent)
{
    ENTITY_COMPONENT_SETTER_FIRST(radius)
    {
        self.radius = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER(speed)
    {
        self.speed = lua_tonumber(state, 3);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentNavigationAgent, init)
{
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentNavigationAgent, insert)
{
    Transform transform;
    getTransformFromComponent(state, transform);

    self.agent = & navigation::System::getInstance().getWorld(self.worldIndex).getWorld().createAgent(*(tilemover2d::Vector2 *) & transform.position);
    self.agent->radius = self.radius;
    self.agent->speed = self.speed;
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentNavigationAgent, update)
{
    Transform transform;

    getTransformFromComponent(state, transform);

    transform.position.x = self.agent->getPosition().x;
    transform.position.y = self.agent->getPosition().y;

    updateTransformFromComponent(state, transform);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentNavigationAgent, remove)
{

}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentNavigationAgent, moveTo)
{
    Vector2 position;

    script::get(state, position, 2);

    self.agent->moveTo(*(tilemover2d::Vector2 *) & position);
}
ENTITY_COMPONENT_END()

}
}
