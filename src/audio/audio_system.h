#pragma once

#include "script.h"
#include "primitives.h"
#include "audio_sound.h"

namespace gengine
{
namespace audio
{

class System
{
public:
    SINGLETON(System);

    void init();
    void finalize();

    void playMusic(const char *path, const bool looping);
    void stopMusic();
    void playSound(const Sound *sound, const float volume);
    void setMusicVolume(const float value);
    void setSoundVolume(const float value);

private:

    float
        soundVolume,
        musicVolume;
};

}
}
