#pragma once

#include "primitives.h"
#include "script.h"
#include "array.h"
#include "pointer.h"
#include "vector2.h"
#include "graphics_spriter.h"
#include <string>

namespace gengine
{
namespace graphics
{

class SpriterManagerItem
{
    friend class SpriterManager;

public:
    void init();
    void finalize();

private:
    Pointer<SpriterEntity>
        entity;
    Pointer<SpriterAnimation>
        animation;
};

}
}
