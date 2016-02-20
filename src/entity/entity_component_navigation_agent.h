#pragma once

#include "script.h"
#include "entity_macros.h"
#include "tilemover2d.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentNavigationAgent : public Component
{
public:
    ComponentNavigationAgent();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentNavigationAgent);

protected:
    tilemover2d::Agent
        * agent;
    uint
        worldIndex;
    float
        radius,
        speed;
};

}
}
