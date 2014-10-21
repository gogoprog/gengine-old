#include "audio_sound_manager.h"

#include "audio_sound.h"
#include "debug.h"
#include <cstring>

namespace gengine
{
namespace audio
{

bool SoundManager::internalCreate(Sound * sound, script::State state)
{
    const char * path = lua_tostring(state, 1);
    return sound->setFromFile(path);
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
