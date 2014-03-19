#pragma once

#include "primitives.h"
#include "array.h"

namespace gengine
{
namespace entity
{

class System
{
public:
    SINGLETON(System);

    void init();
    void update(const float dt);

private:
};

}
}
