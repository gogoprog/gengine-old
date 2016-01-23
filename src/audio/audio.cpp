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

    looping = lua_toboolean(state, 2);

    System::getInstance().playMusic(lua_tostring(state, 1), looping);

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

SCRIPT_FUNCTION(setMusicVolume)
{
    float volume;

    volume = lua_tonumber(state, 1);

    System::getInstance().setMusicVolume(volume);

    return 0;
}

SCRIPT_FUNCTION(setSoundVolume)
{
    float volume;

    volume = lua_tonumber(state, 1);

    System::getInstance().setSoundVolume(volume);

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_FUNCTION(playMusic);
    SCRIPT_TABLE_PUSH_FUNCTION(stopMusic);
    SCRIPT_TABLE_PUSH_FUNCTION(playSound);
    SCRIPT_TABLE_PUSH_FUNCTION(setMusicVolume);
    SCRIPT_TABLE_PUSH_FUNCTION(setSoundVolume);

    SoundManager::luaRegister(state);
    lua_setfield(state, -2, "sound");

    lua_setfield(state, -2, "audio");
}

}
}
