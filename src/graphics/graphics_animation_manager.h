#pragma once

#include "primitives.h"
#include "map.h"
#include "graphics_animation.h"
#include "script.h"
#include <string>

namespace gengine
{
namespace graphics
{

class AnimationManager
{

public:
    AnimationManager() = default;

    void init();
    void finalize();

    SINGLETON(AnimationManager);
    static SCRIPT_REGISTERER();
    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(get);

private:
    Map<std::string, Animation*>
        animationMap;
};

}
}
