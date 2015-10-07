#include "entity_component_text.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{
namespace entity
{

ComponentText::ComponentText()
    :
    worldIndex(0)
{
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
    ENTITY_COMPONENT_SETTER(text)
    {
        self.text.setText(lua_tostring(state,3));
        self.text.update();
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentText, init)
{

}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentText, insert)
{
    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.text);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentText, update)
{
    graphics::Text & text = self.text;
    Transform transform;

    getTransformFromComponent(state, transform);

    text.setPosition(transform.position);
    text.setRotation(transform.rotation);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentText, remove)
{
    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.text);
}
ENTITY_COMPONENT_END()

}
}
