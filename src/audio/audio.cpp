#include "audio.h"

#include "audio_system.h"
#include "audio_sound_manager.h"

namespace gengine
{
namespace audio
{

SCRIPT_FUNCTION(playMusic)
{
    System::getInstance().playMusic(lua_tostring(state,1));

    return 0;
}

SCRIPT_FUNCTION(playSound)
{
    Sound * sound = static_cast<Sound *>(lua_touserdata(state, 1));
    System::getInstance().playSound(sound);

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_FUNCTION(playMusic);
    SCRIPT_TABLE_PUSH_FUNCTION(playSound);

    SoundManager::luaRegister(state);
    lua_setfield(state, -2, "sound");

    lua_setfield(state, -2, "audio");
}

}
}
