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

    void init(int argc, char *argv[]);
    void finalize();
    void update();

private:
};

}
}
