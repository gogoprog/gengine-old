#include "audio.h"

#include "audio_system.h"

namespace gengine
{
namespace audio
{

SCRIPT_FUNCTION(playMusic)
{
    System::getInstance().playMusic(lua_tostring(state,1));

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_FUNCTION(playMusic);

    lua_setglobal(state,"audio");
}

}
}
