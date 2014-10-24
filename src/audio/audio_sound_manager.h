#pragma once

#include "primitives.h"
#include "script.h"
#include "manager.h"
#include <string>

namespace gengine
{
namespace audio
{

class Sound;

class SoundManager : public Manager<Sound>
{

public:
    SoundManager() = default;

    MANAGER_DECLARE(SoundManager);

private:
    virtual bool internalCreate(Sound * atlas, script::State state) override;
    virtual void internalGetName(char * name, const char * arg) override;
};

}
}
