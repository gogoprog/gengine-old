#pragma once

#include "graphics/program.h"

namespace gengine
{
namespace graphics
{

class System
{
public:
    SINGLETON(System);
    void init();

private:
    Program defaultProgram;
};

}
}