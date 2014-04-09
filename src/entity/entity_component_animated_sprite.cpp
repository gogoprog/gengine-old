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

SCRIPT_CLASS_REGISTERER(ComponentAnimatedSprite)
{
}

SCRIPT_CLASS_FUNCTION(ComponentAnimatedSprite, create)
{
    return System::getInstance().createComponent<ComponentAnimatedSprite>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentAnimatedSprite, newIndex)
{
    SCRIPT_GET_SELF(ComponentAnimatedSprite);
    const char * key = lua_tostring(state, 2);

    ComponentSprite::newIndex(state);

    if(!strcmp(key, "animation"))
    {
        self.animation = static_cast<const graphics::Animation *>(lua_touserdata(state, 3));
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentAnimatedSprite, update)
{
    SCRIPT_GET_SELF(ComponentAnimatedSprite);

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

uint
    ComponentAnimatedSprite::metaTableRef;

}
}
