#include "entity_component_sprite_batch.h"

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

ComponentSpriteBatch::ComponentSpriteBatch()
    :
    worldIndex(0)
{
}

SCRIPT_CLASS_REGISTERER(ComponentSpriteBatch)
{
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(ComponentSpriteBatch, lock);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(ComponentSpriteBatch, unlock);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(ComponentSpriteBatch, addItem);
}

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, create)
{
    return System::getInstance().createComponent<ComponentSpriteBatch>(state);
}

ENTITY_COMPONENT_SETTERS(ComponentSpriteBatch)
{
    ENTITY_COMPONENT_SETTER(layer)
    {
        self.spriteBatch.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(atlas)
    {
        graphics::Atlas * atlas = static_cast<graphics::Atlas *>(lua_touserdata(state, 3));
        self.spriteBatch.setAtlas(* atlas);
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER(size)
    {
        self.spriteBatch.reserve(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, init)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    self.spriteBatch.init();

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, insert)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.spriteBatch);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, update)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    graphics::SpriteBatch & spriteBatch = self.spriteBatch;

    Transform transform;
    fillTransformFromComponent(state, transform);

    spriteBatch.setPosition(transform.position);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, remove)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.spriteBatch);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, lock)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    self.spriteBatch.lock();

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, unlock)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    self.spriteBatch.unlock();

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSpriteBatch, addItem)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    Vector2 position, extent;
    int atlas_item_index;

    atlas_item_index = lua_tonumber(state, 2);
    Vector2::fill(state, position, 3);

    if(lua_istable(state, 4))
    {
        Vector2::fill(state, extent, 4);
        self.spriteBatch.addItem(atlas_item_index, position, extent);
    }
    else
    {
        self.spriteBatch.addItem(atlas_item_index, position);
    }

    return 0;
}
uint
    ComponentSpriteBatch::metaTableRef;

}
}
