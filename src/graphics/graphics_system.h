#pragma once

#include "graphics_program.h"

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