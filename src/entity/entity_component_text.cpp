#include "entity_component_text.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
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

ComponentText::ComponentText()
    :
    Component(),
    worldIndex(0)
{
}

void ComponentText::init()
{

}

void ComponentText::insert()
{
    graphics::System::getInstance().getWorld(worldIndex).addObject(text);
}

void ComponentText::update(const float dt)
{
    Transform & transform = entity->transform;

    text.setPosition(transform.position);
    text.setRotation(transform.rotation);
    text.scale(transform.scale);
}

void ComponentText::remove()
{
    graphics::System::getInstance().getWorld(worldIndex).removeObject(text);
}

ENTITY_COMPONENT_IMPLEMENT(ComponentText)
{
}

ENTITY_COMPONENT_SETTERS(ComponentText)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
    {
        self.text.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(font)
    {
        graphics::Font * font = static_cast<graphics::Font *>(lua_touserdata(state, 3));
        self.text.setFont(*font);
        self.text.update();
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER(color)
    {
        Vector4::fill(state, self.text.getColor(), 3);
    }
    ENTITY_COMPONENT_SETTER(alpha)
    {
        self.text.setColorAlpha(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(text)
    {
        self.text.setText(lua_tostring(state,3));
        self.text.update();
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

}
}
