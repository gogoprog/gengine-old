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
    static SCRIPT_FUNCTION(load);
    static SCRIPT_FUNCTION(get);

private:
    static void getBaseName(char * result, const char * file_path);

    Map<std::string, Animation*>
        animationMap;
};

}
}
