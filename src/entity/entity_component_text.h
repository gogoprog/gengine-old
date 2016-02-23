#pragma once

#include "script.h"
#include "entity_macros.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentText : public Component
{
public:
    ComponentText();

    virtual void init();
    virtual void insert();
    virtual void update(const float dt);
    virtual void remove();

    ENTITY_COMPONENT_DECLARE(ComponentText);

protected:
    uint
        worldIndex;
};

}
}
