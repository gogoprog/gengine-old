#include "audio_sound_manager.h"

#include "audio_sound.h"
#include "debug.h"
#include <cstring>

namespace gengine
{
namespace audio
{

Sound * SoundManager::internalCreate(script::State state, const int parameter_position)
{
    auto sound = new Sound();
    const char * path = lua_tostring(state, parameter_position);
    sound->setFromFile(path);

    return sound;
}

void SoundManager::internalGetName(char * result, const char * file_path)
{
    const char * begin, * end;
    uint length;

    if(!(begin = strrchr(file_path,'/')))
    {
        begin = file_path;
    }
    else
    {
        ++begin;
    }

    if(!(end = strrchr(begin,'.')))
    {
        end = begin + strlen(begin);
    }

    length = end - begin;

    strncpy(result, begin, length);
    result[length] = 0;
}

}
}
