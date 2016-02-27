#include "entity_entity.h"

#include "entity_component.h"
#include "application.h"
#include "core.h"
#include <Urho3D/Urho2D/Drawable2D.h>

namespace gengine
{
namespace entity
{

Entity::Entity()
    :
    itIsInserted(false),
    node(nullptr)
{
}

bool Entity::drivesTransform() const
{
    for(auto component : components)
    {
        if(component->drivesTransform())
        {
            return true;
        }
    }

    return false;
}

void Entity::addComponent(Component & component)
{
    components.add(& component);
}

void Entity::init()
{
    node = application::getScene().CreateChild();
    node->SetEnabled(false);
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
        node->SetEnabled(true);

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
        node->SetEnabled(false);

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
