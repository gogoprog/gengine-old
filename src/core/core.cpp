#include "core.h"

#include "core_sdl.h"
#include "input_system.h"
#include "graphics_system.h"
#include "graphics_opengl.h"
#include "application_window.h"
#include "script_system.h"
#include "entity_system.h"
#include "gui_system.h"
#include "audio_system.h"
#include "physics_system.h"
#include "navigation_system.h"
#include "debug.h"
#include "application.h"

namespace gengine
{
namespace core
{

void handleEvents();

bool
    itMustQuit = false;
unsigned long long
    lastTicks = 0,
    currentTicks,
    frameIndex = 0;
float
    updateFactor = 1.0f;
application::Window
    mainWindow;
Urho3D::SharedPtr<Urho3D::Context>
    context;
Urho3D::SharedPtr<application::Application>
    urhoApplication;

bool mustQuit()
{
    return itMustQuit;
}

application::Window getMainWindow()
{
    return mainWindow;
}

bool init(int argc, char *argv[])
{
    geDebugLog("core::init()");

    gui::System::getInstance().preinit(argc,argv);

    script::System & script_system = script::System::getInstance();

    SDL_Init(SDL_INIT_AUDIO);

    script_system.init();

    if(!script_system.executeFile("main.lua"))
    {
        geLog("Cannot load \"main.lua\". Exiting.");
        return false;
    }

    script_system.call("init");

    context = new Urho3D::Context();
    urhoApplication = new gengine::application::Application(context);

    //graphics::System::getInstance().init();
    //input::System::getInstance().init();
    //entity::System::getInstance().init();
    gui::System::getInstance().init(argc,argv);
    audio::System::getInstance().init();
    //physics::System::getInstance().init();
    //navigation::System::getInstance().init();

    script_system.init2();

    script_system.call("start");

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
    navigation::System::getInstance().finalize();
    physics::System::getInstance().finalize();
    audio::System::getInstance().finalize();
    gui::System::getInstance().finalize();

    script::System::getInstance().call("stop");

    graphics::System::getInstance().finalize();

    mainWindow.finalize();

    script::System::getInstance().finalize();

    SDL_Quit();
}

void update()
{
    float dt;

    currentTicks = SDL_GetTicks();
    dt = ( ( currentTicks - lastTicks ) * updateFactor )/ 1000.0f;

    //glClear(GL_COLOR_BUFFER_BIT);

    //handleEvents();

    script::System::getInstance().call1("update", dt);

    //physics::System::getInstance().update(dt);
    //navigation::System::getInstance().update(dt);
    entity::System::getInstance().update(dt);
    //graphics::System::getInstance().update();
    //gui::System::getInstance().update(dt);

    //graphics::System::getInstance().render();
    //gui::System::getInstance().render();

    //input::System::getInstance().update();

    //mainWindow.swap();

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

void handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
            {
                itMustQuit = true;
            }
            break;

            case SDL_MOUSEMOTION:
            {
                SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent*)&e;

                input::System::getInstance().updateMouseCoordinates(0, m->x, m->y);
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&e;

                input::System::getInstance().updateMouseButton(0, m->button, input::Mouse::DOWN);
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&e;

                input::System::getInstance().updateMouseButton(0, m->button, input::Mouse::UP);
            }
            break;

            case SDL_MOUSEWHEEL:
            {
                SDL_MouseWheelEvent *w = (SDL_MouseWheelEvent*)&e;
                int value = w->y;

                #ifdef EMSCRIPTEN
                    value /= std::abs(value) * -1.0f;
                #endif

                input::System::getInstance().updateMouseWheel(0, value);
            }
            break;

            case SDL_KEYDOWN:
            {
                input::System::getInstance().updateKeyboardState(e.key.keysym.scancode, true);
            }
            break;

            case SDL_KEYUP:
            {
                input::System::getInstance().updateKeyboardState(e.key.keysym.scancode, false);
            }
            break;

            case SDL_JOYBUTTONDOWN:
            {
                input::System::getInstance().updateJoypadButton(e.jbutton.which, e.jbutton.button, true);
            }
            break;

            case SDL_JOYBUTTONUP:
            {
                input::System::getInstance().updateJoypadButton(e.jbutton.which, e.jbutton.button, false);
            }
            break;

            #ifndef EMSCRIPTEN
                case SDL_JOYDEVICEADDED:
                {
                    input::System::getInstance().onJoypadConnected(e.jdevice.which);
                }
                break;

                case SDL_JOYDEVICEREMOVED:
                {
                    input::System::getInstance().onJoypadDisconnected(e.jdevice.which);
                }
                break;
            #endif

            case SDL_JOYAXISMOTION:
            {
                input::System::getInstance().updateJoypadAxis(e.jaxis.which, e.jaxis.axis, e.jaxis.value / 32767.0f);
            }
            break;

            case SDL_JOYHATMOTION:
            {
                input::System::getInstance().updateJoypadHat(e.jhat.which, e.jhat.hat, e.jhat.value);
            }
            break;
        }
    }
}

}
}
