#pragma once

#include "primitives.h"
#include "script.h"
#include "array.h"
#include "pointer.h"
#include "maths.h"
#include "map.h"
#include <string>
#include <spine/spine.h>

namespace gengine
{
namespace graphics
{

class SpineManagerItem
{
    friend class SpineManager;

public:
    void init();
    void finalize();

    spSkeletonData *getSkeletonData() { return skeletonData; }
    spAnimationStateData *getAnimationStateData() { return animationStateData; }
    spAnimation *getAnimation() { return animation;; }

private:
    Pointer<spSkeletonData>
        skeletonData;
    Pointer<spAnimation>
        animation;
    Pointer<spAnimationStateData>
        animationStateData;
};

}
}
