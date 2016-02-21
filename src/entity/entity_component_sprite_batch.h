#pragma once

#include "script.h"
#include "graphics_sprite_batch.h"
#include "graphics_atlas.h"
#include "entity_macros.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentSpriteBatch : Component
{
public:
    ComponentSpriteBatch();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentSpriteBatch);

protected:
    graphics::SpriteBatch
        spriteBatch;
    Pointer<graphics::Atlas>
        atlas;
    uint
        worldIndex,
        size;
};

}
}
