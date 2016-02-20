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
#include "entity_entity.h"

namespace gengine
{
namespace entity
{

ComponentSpriteBatch::ComponentSpriteBatch()
    :
    Component(),
    worldIndex(0),
    size(128)
{
}

void ComponentSpriteBatch::init()
{
    spriteBatch.init(size * 4);
}

void ComponentSpriteBatch::insert()
{
    graphics::System::getInstance().getWorld(worldIndex).addObject(spriteBatch);
}

void ComponentSpriteBatch::update(const float /*dt*/)
{
    Transform & transform = entity->transform;

    spriteBatch.setPosition(transform.position);
}

void ComponentSpriteBatch::remove()
{
    graphics::System::getInstance().getWorld(worldIndex).removeObject(spriteBatch);
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSpriteBatch)
{
    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        lock,
        {
            SCRIPT_GET_SELF(ComponentSpriteBatch);
            self.spriteBatch.lock();
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        unlock,
        {
            SCRIPT_GET_SELF(ComponentSpriteBatch);
            self.spriteBatch.unlock();
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        addItem,
        {
            SCRIPT_GET_SELF(ComponentSpriteBatch);
            Vector2 position;
            int atlas_item_index;

            atlas_item_index = lua_tonumber(state, 2);
            script::get(state, position, 3);

            if(lua_istable(state, 4))
            {
                Vector2 extent;
                script::get(state, extent, 4);
                self.spriteBatch.addItem(self.atlas, atlas_item_index, position, extent);
            }
            else
            {
                self.spriteBatch.addItem(self.atlas, atlas_item_index, position);
            }

            return 0;
        }
        );
}

ENTITY_COMPONENT_SETTERS(ComponentSpriteBatch)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
    {
        self.spriteBatch.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(atlas)
    {
        self.atlas = static_cast<graphics::Atlas *>(lua_touserdata(state, 3));
        self.spriteBatch.setTexture(self.atlas->getTexture());
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

}
}
