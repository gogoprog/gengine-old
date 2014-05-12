#include "graphics_animation_manager.h"

#include "debug.h"
#include <cstring>

namespace gengine
{
namespace graphics
{

bool AnimationManager::internalCreate(Animation * animation, script::State state)
{
    return animation->set(state);
}

void AnimationManager::internalGetName(char * result, const char * arg)
{
    strcpy(result, arg);
}

}
}
