#pragma once

#include "primitives.h"
#include "map.h"
#include "graphics_animation.h"
#include "script.h"
#include "manager.h"
#include <string>

namespace gengine
{
namespace graphics
{

class AnimationManager : public Manager<Animation>
{

public:
    AnimationManager() = default;

    MANAGER_DECLARE(AnimationManager);

private:
    virtual bool internalCreate(Animation * animation, script::State state, const int parameter_position) override;
    virtual void internalGetName(char * name, const char * arg) override;
};

}
}
