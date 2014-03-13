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
    void test();

    struct Vertex
    {
        float x, y;
        float r, g, b, a;
        float s, t;
    };

private:
    Program defaultProgram;
};

}
}
