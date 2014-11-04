#include "entity_component_animated_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "graphics_animation.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{
namespace entity
{

ComponentAnimatedSprite::ComponentAnimatedSprite()
    :
    ComponentSprite(),
    animation(nullptr),
    currentTime(0.0f)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentAnimatedSprite)
{
}

ENTITY_COMPONENT_SETTERS(ComponentAnimatedSprite)
{
    ENTITY_COMPONENT_SETTER_FIRST(animation)
    {
        self.animation = static_cast<const graphics::Animation *>(lua_touserdata(state, 3));
    }
    ENTITY_COMPONENT_SETTER_DEFAULT()
    {
        ComponentSprite::newIndex(state);
    }
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentAnimatedSprite, update)
{
    if(self.animation)
    {
        self.currentTime += System::getInstance().getCurrentDt();

        const graphics::AnimationFrame & frame = self.animation->getFrame(self.currentTime);

        self.sprite.setTexture(frame.atlas->getTexture());
        self.sprite.setUvOffset(frame.uvOffset);
        self.sprite.setUvScale(frame.uvScale);
    }

    return ComponentSprite::update(state);
}
ENTITY_COMPONENT_END()

}
}
