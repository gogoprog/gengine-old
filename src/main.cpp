#include "debug.h"
#include "core.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

using namespace gengine;

int main()
{
    core::init();

    #ifndef EMSCRIPTEN
        while(!core::mustQuit())
        {
            core::update();
        }

        core::finalize();
    #else
        emscripten_set_main_loop(core::update(), 0, 0);
    #endif

    return 0;
}