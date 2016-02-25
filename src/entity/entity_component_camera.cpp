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

void ComponentCamera::insert()
{
    auto viewport = new Urho3D::Viewport(&core::getContext(), &application::getScene(0), urhoComponent);
    core::getRenderer().SetViewport(0, viewport);
}

void ComponentCamera::remove()
{
}

}
}
