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

    void playMusic(const char *path, const float volume, const bool looping);
    void playSound(const Sound *sound, const float volume);

private:

};

}
}
