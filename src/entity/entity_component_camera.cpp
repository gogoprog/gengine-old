#include "entity_component_camera.h"

#include "entity.h"
#include "entity_macros.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include "application.h"
#include "core.h"

namespace gengine
{
namespace entity
{

ComponentCamera::ComponentCamera()
    :
    Component()
{
}

void ComponentCamera::init()
{
    camera = entity->getNode().CreateComponent<Urho3D::Camera>();
}

void ComponentCamera::insert()
{
    auto viewport = new Urho3D::Viewport(&core::getContext(), &application::getScene(0), camera);
    core::getRenderer().SetViewport(0, viewport);
}

void ComponentCamera::update(const float /*dt*/)
{
}

void ComponentCamera::remove()
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentCamera)
{
    /*SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        getWorldPosition,
        {
            SCRIPT_GET_SELF(ComponentCamera);
            Vector2 result;
            Vector2 input;

            script::get(state, input, 2);
            self.camera.getWorldPosition(result, input);
            script::push(state, result);

            return 1;
        }
    );*/
}

ENTITY_COMPONENT_SETTERS(ComponentCamera)
{
    ENTITY_COMPONENT_SETTER_FIRST(extent)
    {
        auto extent = script::get<math::Vector2>(state, 3);

        self.camera->SetOrthographic(true);
        self.camera->SetOrthoSize(*extent);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

}
}
