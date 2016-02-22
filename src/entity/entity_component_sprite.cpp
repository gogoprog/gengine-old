#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
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
    atlas(nullptr),
    extent(math::Vector2::zero),
    worldIndex(0),
    atlasItem(0),
    extentHasBeenSet(false),
    staticSprite(nullptr)
{
}

void ComponentSprite::init()
{
    staticSprite = entity->getNode().CreateComponent<Urho3D::StaticSprite2D>();

    return;
    /*
    if(atlas)
    {
        sprite.setTexture(atlas->getTexture());
        const graphics::AtlasItem & item = atlas->getItem(atlasItem);
        sprite.setUvOffset(item.uvOffset);
        sprite.setUvScale(item.uvScale);

        if(!extentHasBeenSet)
        {
            atlas->getDefaultExtent(extent, atlasItem);
        }
    }
    else
    {
        if(!extentHasBeenSet)
        {
            const Pointer<const graphics::Texture> texture = sprite.getTexture();

            if(!texture.isNull())
            {
                extent.x = texture->getWidth();
                extent.y = texture->getHeight();
            }
        }
    }*/
}

void ComponentSprite::insert()
{
}

void ComponentSprite::update(const float dt)
{
    Transform & transform = entity->transform;

    sprite.setPosition(transform.position);
    sprite.setRotation(transform.rotation);
    sprite.setExtent(extent * transform.scale);
}

void ComponentSprite::remove()
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSprite)
{
    ENTITY_ADD_GETTER(ComponentSprite, "extent", { script::push(state, self.sprite.getExtent()); });
}

ENTITY_COMPONENT_SETTERS(ComponentSprite)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
    {
        self.sprite.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(extent)
    {
        script::get(state, self.extent, 3);
        self.extentHasBeenSet = true;
    }
    ENTITY_COMPONENT_SETTER(uvScale)
    {
        script::get(state, self.sprite.getUvScale(), 3);
    }
    ENTITY_COMPONENT_SETTER(uvOffset)
    {
        script::get(state, self.sprite.getUvOffset(), 3);
    }
    ENTITY_COMPONENT_SETTER(color)
    {
        Vector4::fill(state, self.sprite.getColor(), 3);
    }
    ENTITY_COMPONENT_SETTER(alpha)
    {
        self.sprite.setColorAlpha(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(texture)
    {
        auto name = lua_tostring(state, 3);

        auto sprite = core::getResourceCache().GetResource<Urho3D::Sprite2D>(name);

        self.staticSprite->SetSprite(sprite);
    }
    ENTITY_COMPONENT_SETTER(atlas)
    {
        self.atlas = static_cast<graphics::Atlas *>(lua_touserdata(state, 3));
    }
    ENTITY_COMPONENT_SETTER(atlasItem)
    {
        self.atlasItem = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

}
}
