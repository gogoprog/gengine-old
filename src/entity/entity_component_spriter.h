#pragma once

#include "script.h"
#include "entity_macros.h"
#include "graphics_spriter_manager_item.h"
#include "graphics_spriter.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentSpriter : public Component
{
public:
    ComponentSpriter();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentSpriter);

protected:
    void setAnimation(const graphics::SpriterManagerItem * animation, const bool reset_time);

    Pointer<const graphics::SpriterMainlineKey>
        currentMainlineKey;
    Pointer<const graphics::SpriterCharacterMap>
        characterMap;
    Pointer<const graphics::SpriterEntity>
        lastSpriterEntity;
    const graphics::SpriterManagerItem
        * animation;
    Array<const graphics::SpriterManagerItem *>
        animationStack;
    std::string
        characterMapName;
    float
        currentTime,
        timeFactor;
    uint
        worldIndex,
        currentUintTime,
        previousUintTime;
};

}
}
