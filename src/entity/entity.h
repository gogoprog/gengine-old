#pragma once

#include "script.h"
#include "entity_transform.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

int getMetaTableRef();

SCRIPT_REGISTERER();

void fillTransform(lua_State *state, Transform & transform, const int position = -1);
void fillTransformFromComponent(lua_State *state, Transform & transform);

void updateTransform(lua_State *state, const Transform & transform, const int position = -1);
void updateTransformFromComponent(lua_State *state, const Transform & transform);

}
}
