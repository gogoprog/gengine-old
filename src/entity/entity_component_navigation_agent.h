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

    ENTITY_COMPONENT_DECLARE();

protected:
    tilemover2d::Agent
        * agent;
    uint
        worldIndex;
};

}
}
