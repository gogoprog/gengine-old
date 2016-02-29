#include "core.h"

#include "core_sdl.h"
#include "input_system.h"
#include "script_system.h"
#include "entity_system.h"
#include "gui_system.h"
#include "audio_system.h"
#include "debug.h"
#include "application.h"

namespace gengine
{
namespace core
{

bool
    itMustQuit = false;
unsigned long long
    lastTicks = 0,
    currentTicks,
    frameIndex = 0;
float
    updateFactor = 1.0f;
Urho3D::SharedPtr<Urho3D::Context>
    context;
Urho3D::SharedPtr<application::Application>
    urhoApplication;
int
    _argc;
char
    ** _argv;

int  getArgc()
{
    return _argc;
}

char **getArgv()
{
    return _argv;
}

bool mustQuit()
{
    return itMustQuit;
}

bool init(int argc, char *argv[])
{
    geDebugLog("core::init()");

    _argc = argc;
    _argv = argv;

    gui::System::getInstance().preinit(argc, argv);

    script::System & script_system = script::System::getInstance();

    SDL_Init(SDL_INIT_AUDIO);
    context = new Urho3D::Context();

    script_system.init();

    if(!script_system.executeFile("main.lua"))
    {
        geLog("Cannot load \"main.lua\". Exiting.");
        return false;
    }

    script_system.call("init");

    urhoApplication = new gengine::application::Application(context);

    input::System::getInstance().init();
    entity::System::getInstance().init();
    audio::System::getInstance().init();

    return true;
}

int run()
{
    return urhoApplication->Run();
}

void finalize()
{
    geDebugLog("core::finalize()");

    input::System::getInstance().finalize();
    audio::System::getInstance().finalize();
    gui::System::getInstance().finalize();

    script::System::getInstance().call("stop");

    script::System::getInstance().finalize();
}

void update()
{
    float dt;

    currentTicks = SDL_GetTicks();
    dt = ( ( currentTicks - lastTicks ) * updateFactor )/ 1000.0f;

    script::System::getInstance().call1("update", dt);

    entity::System::getInstance().update(dt);
    //gui::System::getInstance().update(dt);

    //gui::System::getInstance().render();

    input::System::getInstance().update();

    lastTicks = currentTicks;

    ++frameIndex;
}

void setMustQuit(const bool it_must_quit)
{
    itMustQuit = it_must_quit;
}

void setUpdateFactor(const float factor)
{
    updateFactor = factor;
}

Urho3D::Context & getContext()
{
    return *context;
}

Urho3D::ResourceCache & getResourceCache()
{
    return *urhoApplication->GetSubsystem<Urho3D::ResourceCache>();
}

Urho3D::Renderer & getRenderer()
{
    return *urhoApplication->GetSubsystem<Urho3D::Renderer>();
}

Urho3D::FileSystem & getFileSystem()
{
    return *urhoApplication->GetSubsystem<Urho3D::FileSystem>();
}

Urho3D::Input & getInput()
{
    return *urhoApplication->GetSubsystem<Urho3D::Input>();
}

Urho3D::UI & getUI()
{
    return *urhoApplication->GetSubsystem<Urho3D::UI>();
}

}
}
