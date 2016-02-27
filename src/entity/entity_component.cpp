#include "entity_component.h"


namespace gengine
{
namespace entity
{

Component::Component()
    :
    itDrivesTransform(false)
{
}

void Component::init()
{
}

void Component::finalize()
{
}

void Component::insert()
{
}

void Component::update(const float /*dt*/)
{
}

void Component::remove()
{
}

void Component::onPropertySet(const char * /*name*/)
{
}

}
}
