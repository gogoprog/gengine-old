#include "entity_component_quad.h"

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

ComponentQuad::ComponentQuad()
    :
    Component(),
    worldIndex(0)
{
}

void ComponentQuad::init()
{
    //sprite.setTexture(graphics::System::getInstance().getWhiteTexture());
}

void ComponentQuad::insert()
{
    //graphics::System::getInstance().getWorld(worldIndex).addObject(sprite);
}

void ComponentQuad::update(const float /*dt*/)
{
    math::Transform & transform = entity->transform;

    /*sprite.setPosition(transform.position);
    sprite.setRotation(transform.rotation);*/
}

void ComponentQuad::remove()
{
    //graphics::System::getInstance().getWorld(worldIndex).removeObject(sprite);
}

ENTITY_COMPONENT_IMPLEMENT(ComponentQuad)
{
    //ENTITY_ADD_GETTER(ComponentQuad, "extent", { script::push(state, self.sprite.getExtent()); });
}

ENTITY_COMPONENT_SETTERS(ComponentQuad)
{
    /*ENTITY_COMPONENT_SETTER_FIRST(layer)
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
    ENTITY_COMPONENT_SETTER_END()*/
}
ENTITY_COMPONENT_END()

}
}
