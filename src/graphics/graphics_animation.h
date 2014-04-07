#pragma once

#include "primitives.h"
#include "graphics_animation_frame.h"
#include "script.h"
#include "array.h"

namespace gengine
{
namespace graphics
{

class Animation
{
friend class AnimationManager;

public:
    Animation();
    void init();
    void finalize();
    bool setFromTable(lua_State * state);

private:
    Array<AnimationFrame>
        frameTable;
    float
        frameRate;
};

}
}
