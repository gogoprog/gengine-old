#pragma once

#include "primitives.h"

namespace gengine
{
namespace gui
{

class System
{
public:
    SINGLETON(System);

    void init();
    void finalize();

private:
};

}
}
