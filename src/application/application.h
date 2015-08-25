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
math::Vector2 getExtent();
void setExtent(const uint width, const uint height);
bool isFullscreen();

SCRIPT_REGISTERER();

}
}
