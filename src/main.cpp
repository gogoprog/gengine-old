#include "debug.h"
#include "core.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

using namespace gengine;

int main(int argc, char *argv[])
{
    if(core::init(argc, argv))
    {
        #ifndef EMSCRIPTEN
            while(!core::mustQuit())
            {
                core::update();
            }

            core::finalize();
        #else
            emscripten_set_main_loop(core::update, 0, 0);
        #endif
    }

    return 0;
}