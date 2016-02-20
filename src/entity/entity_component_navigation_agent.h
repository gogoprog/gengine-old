#pragma once

#include "script.h"
#include "entity_macros.h"
#include "tilemover2d.h"

namespace gengine
{
namespace entity
{

class ComponentNavigationAgent
{
public:
    ComponentNavigationAgent();

    ENTITY_COMPONENT_DECLARE_OLD(ComponentNavigationAgent);

    ENTITY_COMPONENT_METHOD_DECLARE(moveTo);

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
