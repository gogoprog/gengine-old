#pragma once

#include "script.h"
#include "entity_macros.h"
#include "graphics_spine_manager_item.h"
#include "graphics_mesh.h"
#include "graphics_vertex.h"

namespace gengine
{
namespace entity
{

class ComponentSpine
{
public:
    ComponentSpine();
    ~ComponentSpine();

    ENTITY_COMPONENT_METHOD_DECLARE(setAnimation);
    ENTITY_COMPONENT_METHOD_DECLARE(addAnimation);

    ENTITY_COMPONENT_DECLARE(ComponentSpine);

protected:

    void setAnimation(const graphics::SpineManagerItem * animation, const int track_index, const bool loop);
    void addAnimation(const graphics::SpineManagerItem * animation, const int track_index, const bool loop, const float delay);
    void updateSpine(graphics::SpineManagerItem & animation);

    graphics::Mesh<graphics::Vertex>
        mesh;
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
