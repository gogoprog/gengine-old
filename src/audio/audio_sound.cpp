#include "audio_sound.h"

#include "debug.h"
#include "core_sdl.h"

namespace gengine
{
namespace audio
{

void Sound::init()
{
}

void Sound::finalize()
{
}

bool Sound::setFromFile(const char *file_path)
{
    geDebugLogN("audio::Sound::setFromFile \"" << file_path << "\" ... ");

    chunk = Mix_LoadWAV(file_path);

    if(chunk == nullptr)
    {
        geDebugRawLog("Failed!");

        return false;
    }

    geDebugRawLog("Ok!");

    return true;
}

}
}
