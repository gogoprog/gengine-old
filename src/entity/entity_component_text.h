#pragma once

#include "script.h"
#include "graphics_text.h"
#include "entity_macros.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentText : public Component
{
public:
    ComponentText();

    virtual void init();
    virtual void insert();
    virtual void update(const float dt);
    virtual void remove();

    ENTITY_COMPONENT_DECLARE(ComponentText);

protected:
    graphics::Text
        text;
    uint
        worldIndex;
};

}
}
