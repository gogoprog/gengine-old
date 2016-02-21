#include "entity_component_navigation_agent.h"

#include "navigation_system.h"
#include "navigation_world.h"
#include "script.h"
#include "script_system.h"
#include "debug.h"
#include <string.h>
#include "entity.h"
#include "entity_entity.h"
#include "entity_system.h"

namespace gengine
{

using namespace math;

namespace entity
{

ComponentNavigationAgent::ComponentNavigationAgent()
    :
    Component(),
    agent(nullptr),
    worldIndex(0),
    radius(10.0f),
    speed(100.0f)
{
}

void ComponentNavigationAgent::init()
{
}

void ComponentNavigationAgent::insert()
{
    Transform & transform = entity->transform;

    agent = & navigation::System::getInstance().getWorld(worldIndex).getWorld().createAgent(*(tilemover2d::Vector2 *) & transform.position);
    agent->radius = radius;
    agent->speed = speed;
}

void ComponentNavigationAgent::update(const float /*dt*/)
{
    Transform & transform = entity->transform;

    transform.position.x = agent->getPosition().x;
    transform.position.y = agent->getPosition().y;

    script::update(script::System::getInstance().getState(), transform);
}

void ComponentNavigationAgent::remove()
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentNavigationAgent)
{
    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        moveTo,
        {
            SCRIPT_GET_SELF(ComponentNavigationAgent);
            Vector2 position;

            script::get(state, position, 2);

            self.agent->moveTo(*(tilemover2d::Vector2 *) & position);

            return 0;
        }
        );
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

}
}
