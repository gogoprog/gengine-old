#pragma once

#include "primitives.h"
#include "script.h"
#include "vector2.h"

struct lua_State;

namespace gengine
{
namespace application
{

const char * getName();
uint getWidth();
uint getHeight();
Vector2 getExtent();
bool isFullscreen();

SCRIPT_REGISTERER();

}
}
