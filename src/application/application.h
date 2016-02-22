#pragma once

#include "primitives.h"
#include "script.h"
#include "vector2.h"
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Scene/Scene.h>

struct lua_State;

namespace gengine
{
namespace application
{

const char * getName();
uint getWidth();
uint getHeight();
math::Vector2 getExtent();
void setExtent(const uint width, const uint height);
bool isFullscreen();
Urho3D::Scene & getScene(const uint index = 0);

SCRIPT_REGISTERER();

class Application : public Urho3D::Application
{
    URHO3D_OBJECT(Application, Application);

public:
    Application(Urho3D::Context* context);

    virtual void Setup() override;
    virtual void Start() override;
    virtual void Stop() override;

    void Update(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
};

}
}
