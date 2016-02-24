#include "entity_component_sprite.h"

#include "entity_system.h"
#include "entity_entity.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"
#include "core.h"
#include "application.h"

namespace gengine
{
namespace entity
{

ComponentSprite::ComponentSprite()
    :
    staticSprite(nullptr)
{
}

void ComponentSprite::init()
{
    staticSprite = entity->getNode().CreateComponent<Urho3D::StaticSprite2D>();
}

void ComponentSprite::insert()
{
}

void ComponentSprite::update(const float dt)
{

}

void ComponentSprite::remove()
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSprite)
{
    //ENTITY_ADD_GETTER(ComponentSprite, "extent", { script::push(state, self.sprite.getExtent()); });
}

ENTITY_COMPONENT_SETTERS(ComponentSprite)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
    {
        self.staticSprite->SetLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(uvScale)
    {
        //script::get(state, self.sprite.getUvScale(), 3);
    }
    ENTITY_COMPONENT_SETTER(uvOffset)
    {
        //script::get(state, self.sprite.getUvOffset(), 3);
    }
    ENTITY_COMPONENT_SETTER(color)
    {
        //Vector4::fill(state, self.sprite.getColor(), 3);
    }
    ENTITY_COMPONENT_SETTER(alpha)
    {
        self.staticSprite->SetAlpha(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(sprite)
    {
        auto sprite = reinterpret_cast<Urho3D::Sprite2D*>(lua_touserdata(state, 3));

        self.staticSprite->SetSprite(sprite);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

}
}
