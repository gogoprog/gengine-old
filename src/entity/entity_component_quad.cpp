#include "entity_component_quad.h"

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

ComponentQuad::ComponentQuad()
    :
    worldIndex(0)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentQuad)
{
    ENTITY_ADD_GETTER(ComponentQuad, "extent", { script::push(state, self.sprite.getExtent()); });
}

ENTITY_COMPONENT_SETTERS(ComponentQuad)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
    {
        self.sprite.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(extent)
    {
        script::get(state, self.sprite.getExtent(), 3);
    }
    ENTITY_COMPONENT_SETTER(color)
    {
        Vector4::fill(state, self.sprite.getColor(), 3);
    }
    ENTITY_COMPONENT_SETTER(alpha)
    {
        self.sprite.setColorAlpha(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentQuad, init)
{
    self.sprite.setTexture(graphics::System::getInstance().getWhiteTexture());
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentQuad, insert)
{
    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.sprite);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentQuad, update)
{
    graphics::Sprite & sprite = self.sprite;

    Transform transform;
    getTransformFromComponent(state, transform);

    sprite.setPosition(transform.position);
    sprite.setRotation(transform.rotation);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentQuad, remove)
{
    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.sprite);
}
ENTITY_COMPONENT_END()

}
}
