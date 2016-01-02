#include "graphics.h"

#include "script.h"
#include "script_system.h"
#include "gui_system.h"

namespace gengine
{
namespace gui
{

SCRIPT_FUNCTION(loadFile)
{
    const char * file_path = lua_tostring(state, 1);

    System::getInstance().loadFile(file_path);

    return 0;
}

SCRIPT_FUNCTION(executeScript)
{
    const char * code = lua_tostring(state, 1);

    System::getInstance().executeScript(code);

    return 0;
}


SCRIPT_FUNCTION(showPage)
{
    const char * name = lua_tostring(state, 1);
    auto duration = int(lua_tonumber(state, 2));

    System::getInstance().showPage(name, duration);

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_FUNCTION(loadFile);
    SCRIPT_TABLE_PUSH_FUNCTION(executeScript);
    SCRIPT_TABLE_PUSH_FUNCTION(showPage);

    lua_setfield(state, -2, "gui");

    script::System::getInstance().executeText("gengine.stateMachine(gengine.gui)");
}

}
}
