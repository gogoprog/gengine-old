#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"

namespace gengine
{
namespace entity
{

SCRIPT_CLASS_FUNCTION(ComponentSprite, create)
{
    return System::getInstance().createComponent<ComponentSprite>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, init)
{
    SCRIPT_GET_SELF(ComponentSprite);

    lua_getfield(state, 2, "texture");
    uint texture = lua_tonumber(state, -1);

    (void)texture;

    graphics::Sprite & sprite = self.sprite;

    sprite.setLayer(script::getTableIntegerSafe(state, "layer", 2, 0));

    script::fillTableVector2Safe(state, sprite.getExtent(), "extent", 2, Vector2(64,64));

    script::fillTableVector4Safe(state, sprite.getColor(), "color", 2, Vector4::one);


    sprite.setTexture(graphics::System::getInstance().getDefaultTexture());

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, insert)
{
    SCRIPT_GET_SELF(ComponentSprite);

    graphics::System::getInstance().getWorld(0).addSprite(self.sprite);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, update)
{
    SCRIPT_GET_SELF(ComponentSprite);

    graphics::Sprite & sprite = self.sprite;

    System::Transform & transform = System::getInstance().getCurrentTransform();

    sprite.setPosition(transform.position);
    sprite.setRotation(transform.rotation);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, remove)
{
    SCRIPT_GET_SELF(ComponentSprite);

    graphics::System::getInstance().getWorld(0).removeSprite(self.sprite);

    return 0;
}

uint ComponentSprite::metaTableRef;

}
}
