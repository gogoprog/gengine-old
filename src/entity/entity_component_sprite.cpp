#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>

namespace gengine
{
namespace entity
{

SCRIPT_CLASS_FUNCTION(ComponentSprite, create)
{
    return System::getInstance().createComponent<ComponentSprite>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, newIndex)
{
    SCRIPT_GET_SELF(ComponentSprite);
    const char * key = lua_tostring(state, 2);

    if(!strcmp(key,"layer"))
    {
        self.sprite.setLayer(lua_tonumber(state,3));
    }
    else if(!strcmp(key,"extent"))
    {
        script::fillVector2(state, self.sprite.getExtent(), 3);
    }
    else if(!strcmp(key,"color"))
    {
        script::fillVector4(state, self.sprite.getColor(), 3);
    }
    else if(!strcmp(key,"texture"))
    {
        self.sprite.setTexture(graphics::System::getInstance().getDefaultTexture());
    }
    else
    {
        geLog("Unknown attribute \"" << key << "\"");
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, init)
{
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

uint
    ComponentSprite::metaTableRef;

}
}
