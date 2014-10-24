#pragma once

#include "primitives.h"
#include "core_sdl.h"

namespace gengine
{
namespace audio
{

class Sound
{
friend class SoundManager;
friend class System;

public:
    Sound() = default;
    void init();
    void finalize();
    bool setFromFile(const char *file_path);

private:
    Mix_Chunk
        * chunk;
};

}
}
