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
    worldIndex(0),
    size(128)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSpriteBatch)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(lock);
    ENTITY_COMPONENT_PUSH_FUNCTION(unlock);
    ENTITY_COMPONENT_PUSH_FUNCTION(addItem);
}

ENTITY_COMPONENT_SETTERS(ComponentSpriteBatch)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
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
        self.size = uint(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriteBatch, init)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    self.spriteBatch.init(self.size);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriteBatch, insert)
{
    SCRIPT_GET_SELF(ComponentSpriteBatch);

    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.spriteBatch);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriteBatch, update)
{
    graphics::SpriteBatch & spriteBatch = self.spriteBatch;

    Transform transform;
    getTransformFromComponent(state, transform);

    spriteBatch.setPosition(transform.position);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriteBatch, remove)
{
    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.spriteBatch);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriteBatch, lock)
{
    self.spriteBatch.lock();
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriteBatch, unlock)
{
    self.spriteBatch.unlock();
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriteBatch, addItem)
{
    Vector2 position, extent;
    int atlas_item_index;

    atlas_item_index = lua_tonumber(state, 2);
    script::get(state, position, 3);

    if(lua_istable(state, 4))
    {
        script::get(state, extent, 4);
        self.spriteBatch.addItem(atlas_item_index, position, extent);
    }
    else
    {
        self.spriteBatch.addItem(atlas_item_index, position);
    }
}
ENTITY_COMPONENT_END()

}
}
