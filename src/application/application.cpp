#include "application.h"

#include "primitives.h"
#include "script.h"
#include "core.h"
#include <string>

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>

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
}

void Application::Start()
{
}

void Application::Stop()
{
}

URHO3D_DEFINE_APPLICATION_MAIN(Application)

}
}
