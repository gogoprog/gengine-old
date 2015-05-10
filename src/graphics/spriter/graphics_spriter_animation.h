#pragma once

#include "primitives.h"
#include "script.h"
#include "array.h"

namespace gengine
{
namespace graphics
{

class SpriterAnimation
{
    friend class SpriterManager;

public:
    void init();
    void finalize();
};

}
}
