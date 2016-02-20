#include "entity_entity.h"

#include "entity_component.h"

namespace gengine
{
namespace entity
{

Entity::Entity()
    :
    itIsInserted(false)
{
}

void Entity::addComponent(Component & component)
{
    components.add(& component);
}

void Entity::insert()
{
    if(!itIsInserted)
    {
        for(auto component : components)
        {
            component->insert();
        }

        itIsInserted = true;
    }
}

void Entity::remove()
{
    if(itIsInserted)
    {
        for(auto component : components)
        {
            component->remove();
        }

        itIsInserted = false;
    }
}

void Entity::update(const float dt)
{
    for(auto component : components)
    {
        component->update(dt);
    }
}

}
}
