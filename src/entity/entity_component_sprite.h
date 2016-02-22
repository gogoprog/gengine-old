#pragma once

#include "script.h"
#include "graphics_sprite.h"
#include "graphics_atlas.h"
#include "entity_macros.h"
#include "entity_component.h"
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>

namespace gengine
{
namespace entity
{

class ComponentSprite : public Component
{
public:
    ComponentSprite();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentSprite);

protected:
    graphics::Sprite
        sprite;
    graphics::Atlas
        * atlas;
    math::Vector2
        extent;
    uint
        worldIndex,
        atlasItem;
    bool
        extentHasBeenSet;
    Urho3D::SharedPtr<Urho3D::StaticSprite2D>
        staticSprite;
};

}
}
