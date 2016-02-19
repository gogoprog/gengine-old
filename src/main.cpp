#include "debug.h"
#include "core.h"
#include "application.h"
#include <Urho3D/Engine/Application.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

using namespace gengine;

int main(int argc, char *argv[])
{
    if(core::init(argc, argv))
    {
        Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context()); \
        Urho3D::SharedPtr<gengine::application::Application> application(new gengine::application::Application(context)); \
        return application->Run();

        /*
        #ifndef EMSCRIPTEN
            while(!core::mustQuit())
            {
                //core::update();
            }

            //core::finalize();
        #else
            emscripten_set_main_loop(core::update, 0, 0);
        #endif*/
    }

    return 0;
}
