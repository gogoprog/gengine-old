#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{
namespace entity
{

ComponentSprite::ComponentSprite()
    :
    atlas(nullptr),
    worldIndex(0)
{
}

SCRIPT_CLASS_REGISTERER(ComponentSprite)
{
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, create)
{
    return System::getInstance().createComponent<ComponentSprite>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, newIndex)
{
    SCRIPT_GET_SELF(ComponentSprite);
    const char * key = lua_tostring(state, 2);

    if(!strcmp(key, "layer"))
    {
        self.sprite.setLayer(lua_tonumber(state,3));
    }
    else if(!strcmp(key, "extent"))
    {
        script::fillVector2(state, self.sprite.getExtent(), 3);
    }
    else if(!strcmp(key, "uvScale"))
    {
        script::fillVector2(state, self.sprite.getUvScale(), 3);
    }
    else if(!strcmp(key, "uvOffset"))
    {
        script::fillVector2(state, self.sprite.getUvOffset(), 3);
    }
    else if(!strcmp(key, "color"))
    {
        script::fillVector4(state, self.sprite.getColor(), 3);
    }
    else if(!strcmp(key, "alpha"))
    {
        self.sprite.setColorAlpha(lua_tonumber(state,3));
    }
    else if(!strcmp(key, "texture"))
    {
        graphics::Texture * texture = static_cast<graphics::Texture *>(lua_touserdata(state, 3));
        self.sprite.setTexture(*texture);
    }
    else if(!strcmp(key, "atlas"))
    {
        self.atlas = static_cast<graphics::Atlas *>(lua_touserdata(state, 3));
        self.sprite.setTexture(self.atlas->getTexture());
    }
    else if(!strcmp(key, "atlasItem"))
    {
        const graphics::AtlasItem & item = self.atlas->getItem(lua_tonumber(state,3));
        self.sprite.setUvOffset(item.uvOffset);
        self.sprite.setUvScale(item.uvScale);
    }
    else if(!strcmp(key, "world"))
    {
        self.worldIndex = lua_tonumber(state,3);
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

    graphics::System::getInstance().getWorld(self.worldIndex).addSprite(self.sprite);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, update)
{
    SCRIPT_GET_SELF(ComponentSprite);

    graphics::Sprite & sprite = self.sprite;

    Transform transform;
    fillTransformFromComponent(state, transform);

    sprite.setPosition(transform.position);
    sprite.setRotation(transform.rotation);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, remove)
{
    SCRIPT_GET_SELF(ComponentSprite);

    graphics::System::getInstance().getWorld(self.worldIndex).removeSprite(self.sprite);

    return 0;
}

uint
    ComponentSprite::metaTableRef;

}
}
