#include "audio_system.h"

#include "script.h"
#include "core_sdl.h"
#include "debug.h"

namespace gengine
{
namespace audio
{

void System::init()
{
    geDebugLog("audio::System::init()");

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16;
    int audio_channels = 32;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
    {
        geDebugLog("audio::System Unable to open audio!");
    }
}

void System::finalize()
{
    geDebugLog("audio::System::finalize()");

    Mix_CloseAudio();
}

void System::playMusic(const char *path)
{
    Mix_Music * music;

    music = Mix_LoadMUS(path);

    Mix_PlayMusic(music, 0);
}

void System::playSound(const Sound *sound)
{
    Mix_PlayChannel(-1, sound->chunk, 0);
}

}
}
