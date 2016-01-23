#include "audio_system.h"

#include "script.h"
#include "core_sdl.h"
#include "debug.h"
#include "audio_sound_manager.h"

namespace gengine
{
namespace audio
{

void System::init()
{
    geDebugLog("audio::System::init()");

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
    {
        geDebugLog("audio::System Unable to open audio!");
    }

    SoundManager::getInstance().init("sound");
    SoundManager::getInstance().addSupportedExtension(".wav");

    musicVolume = 1.0f;
    soundVolume = 1.0f;
}

void System::finalize()
{
    geDebugLog("audio::System::finalize()");

    SoundManager::getInstance().finalize();

    Mix_CloseAudio();
}

void System::playMusic(const char *path, const bool looping)
{
    Mix_Music * music;

    music = Mix_LoadMUS(path);

    Mix_PlayMusic(music, looping ? -1 : 0);
}

void System::stopMusic()
{
    Mix_HaltMusic();
}

void System::playSound(const Sound *sound, const float volume)
{
    if(sound)
    {
        int channel = Mix_PlayChannel(-1, sound->chunk, 0);
        Mix_Volume(channel, int(MIX_MAX_VOLUME * volume * soundVolume));
    }
    else
    {
        geLog("audio::System::playSound() : Null sound given.")
    }
}

void System::setMusicVolume(const float value)
{
    musicVolume = value;
    Mix_VolumeMusic(int(MIX_MAX_VOLUME * musicVolume));
}

void System::setSoundVolume(const float value)
{
    soundVolume = value;
}

}
}
