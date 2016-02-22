#include "entity_entity.h"

#include "entity_component.h"
#include "application.h"
#include "core.h"

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

void Entity::init()
{
    node = new Urho3D::Node(& core::getContext());
}

void Entity::finalize()
{
    for(auto component : components)
    {
        component->finalize();
        delete component;
    }

    components.setSize(0);
}

void Entity::insert()
{
    if(!itIsInserted)
    {
        application::getScene(0).AddChild(node);

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
