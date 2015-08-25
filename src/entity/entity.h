#pragma once

#include "script.h"
#include "transform.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

int getMetaTableRef();

SCRIPT_REGISTERER();

void getTransformFromComponent(lua_State *state, math::Transform & transform);
void updateTransformFromComponent(lua_State *state, const math::Transform & transform);

}
}
