#pragma once

#include "script.h"
#include "entity_macros.h"
#include "graphics_spine_manager_item.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentSpine : public Component
{
public:
    ComponentSpine();
    ~ComponentSpine();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentSpine);

protected:

    void setAnimation(const graphics::SpineManagerItem * animation, const int track_index, const bool loop);
    void addAnimation(const graphics::SpineManagerItem * animation, const int track_index, const bool loop, const float delay);
    void updateSpine(graphics::SpineManagerItem & animation);

    Pointer<spAnimationState>
        animationState;
    Pointer<spSkeleton>
        skeleton;
    float
        timeFactor;
    uint
        worldIndex,
        size;
};

}
}
