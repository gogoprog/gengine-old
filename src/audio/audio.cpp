#include "audio.h"

#include "audio_system.h"
#include "audio_sound_manager.h"

namespace gengine
{
namespace audio
{

SCRIPT_FUNCTION(playMusic)
{
    bool looping;
    float volume;

    volume = lua_tonumber(state, 2);
    looping = lua_toboolean(state, 3);

    System::getInstance().playMusic(lua_tostring(state, 1), volume, looping);

    return 0;
}

SCRIPT_FUNCTION(stopMusic)
{
    System::getInstance().stopMusic();

    return 0;
}

SCRIPT_FUNCTION(playSound)
{
    Sound * sound = static_cast<Sound *>(lua_touserdata(state, 1));
    float volume;

    volume = lua_tonumber(state, 2);

    System::getInstance().playSound(sound, volume);

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_FUNCTION(playMusic);
    SCRIPT_TABLE_PUSH_FUNCTION(stopMusic);
    SCRIPT_TABLE_PUSH_FUNCTION(playSound);

    SoundManager::luaRegister(state);
    lua_setfield(state, -2, "sound");

    lua_setfield(state, -2, "audio");
}

}
}
