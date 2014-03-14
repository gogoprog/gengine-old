#pragma once

#include "primitives.h"

namespace gengine
{
namespace graphics
{

class Program;

class Uniform
{
friend class Program;

public:
    void init(const Program & program, const char * name);

private:
    uint location;
};

}
}
