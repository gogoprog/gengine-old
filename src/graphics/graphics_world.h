#pragma once

#include "primitives.h"
#include "vector2.h"

namespace gengine
{
namespace graphics
{

class World
{
friend class System;

public:
    World();
    void init();
    void finalize();

private:
};

}
}
