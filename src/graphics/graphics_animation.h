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
    bool set(lua_State * state);

    float getDuration() const { return duration; }
    const AnimationFrame & getFrame(const float time) const;

private:
    Array<AnimationFrame>
        frameTable;
    float
        frameRate,
        frameDuration,
        duration;
};

}
}
