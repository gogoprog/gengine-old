#include "script.h"

#include "script_system.h"
#include <string>

#ifdef EMSCRIPTEN
    #include <emscripten/bind.h>

    using namespace emscripten;
#endif

namespace gengine
{
namespace script
{

void executeText(std::string text)
{
    script::System::getInstance().executeText(text.c_str());
}

#ifdef EMSCRIPTEN
    EMSCRIPTEN_BINDINGS(script_module)
    {
        function<void, std::string>("execute", &executeText);
    }
#endif

}
}
