#pragma once

#include "script.h"
#include "primitives.h"
#include "maths.h"
#include "entity_macros.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentMouseable : public Component
{
public:
    ComponentMouseable();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentMouseable);

private:
    math::Vector2
        extent;
    uint
        worldIndex;
    bool
        itIsHovered;
};

}
}
