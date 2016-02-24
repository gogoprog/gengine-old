#include "application.h"

#include "primitives.h"
#include "script.h"
#include "core.h"
#include "debug.h"
#include "array.h"
#include "script_system.h"
#include <string>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>

namespace gengine
{
namespace application
{

std::string
    name = "gengine";
bool
    fullscreen = false;
uint
    width = 640,
    height = 480;
Array<Urho3D::SharedPtr<Urho3D::Scene>>
    scenes;

SCRIPT_FUNCTION(setName)
{
    name = lua_tostring(state, 1);

    return 0;
}

SCRIPT_FUNCTION(setExtent)
{
    width = uint(lua_tonumber(state, 1));
    height = uint(lua_tonumber(state, 2));

    return 0;
}

SCRIPT_FUNCTION(setFullscreen)
{
    fullscreen = lua_toboolean(state, 1);

    return 0;
}

SCRIPT_FUNCTION(setUpdateFactor)
{
    float factor = uint(lua_tonumber(state, 1));

    core::setUpdateFactor(factor);

    return 0;
}

SCRIPT_FUNCTION(quit)
{
    core::setMustQuit(true);
    return 0;
}

const char * getName() { return name.c_str(); }
uint getWidth() { return width; }
uint getHeight() { return height; }
math::Vector2 getExtent() { return math::Vector2(width, height); }
void setExtent(const uint _width, const uint _height) { width = _width; height = _height; }
bool isFullscreen() { return fullscreen; }
Urho3D::Scene & getScene(const uint index) {return *scenes[index];}

SCRIPT_REGISTERER()
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_FUNCTION(setName);
    SCRIPT_TABLE_PUSH_FUNCTION(setExtent);
    SCRIPT_TABLE_PUSH_FUNCTION(setFullscreen);
    SCRIPT_TABLE_PUSH_FUNCTION(setUpdateFactor);
    SCRIPT_TABLE_PUSH_FUNCTION(quit);
    lua_setfield(state, -2, "application");
}

Application::Application(Urho3D::Context* context)
    :
    Urho3D::Application(context)
{
}

void Application::Setup()
{
    engineParameters_["LogName"] = "gengine.log";
    engineParameters_["LogLevel"] = "Debug";
    engineParameters_["FullScreen"] = fullscreen;
    engineParameters_["Headless"] = false;
    engineParameters_["Sound"] = false;
    engineParameters_["WindowWidth"] = width;
    engineParameters_["WindowHeight"] = height;
    engineParameters_["WindowTitle"] = getName();
    engineParameters_["ResourcePaths"] = "data;coreData;";
    //engineParameters_["AutoloadPaths"] = "data;coreData;";

    engineParameters_["ResourcePrefixPaths"] = (std::string(core::getFileSystem().GetCurrentDir().CString()) + ";" + std::string(getenv("GENGINE")) + "/res/").c_str();
}

void Application::Start()
{
    SubscribeToEvent(Urho3D::E_UPDATE, URHO3D_HANDLER(Application, Update));

    Urho3D::SharedPtr<Urho3D::Scene> scene_(new Urho3D::Scene(context_));
    scene_->CreateComponent<Urho3D::Octree>();
    scenes.add(scene_);

    auto cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->SetPosition(Urho3D::Vector3(0.0f, 0.0f, -10.0f));

    auto camera = cameraNode_->CreateComponent<Urho3D::Camera>();
    camera->SetOrthographic(true);

    auto graphics = GetSubsystem<Urho3D::Graphics>();

    camera->SetOrthoSize(Urho3D::Vector2((float)graphics->GetWidth(), (float)graphics->GetHeight() ));

    scenes.add(scene_);

    auto renderer = GetSubsystem<Urho3D::Renderer>();
    auto viewport = new Urho3D::Viewport(context_, scene_, cameraNode_->GetComponent<Urho3D::Camera>());
    renderer->SetViewport(0, viewport);

    script::System::getInstance().init2();
    script::System::getInstance().call("start");
}

void Application::Stop()
{
}

void Application::Update(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData)
{
    core::update();
}

}
}
