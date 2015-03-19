#pragma once

#include <string>
#include "primitives.h"
#include "graphics_uniform.h"

namespace gengine
{
namespace graphics
{

class Program;

class ParticleModifierUniforms
{
public:
    void init(const Program & program, const char * _basename)
    {
        std::string basename = _basename;

        values.init(program, (basename + "Table").c_str());
        count.init(program, (basename + "Count").c_str());
    }

    template<class T>
    void apply(const Array<T> & value_table)
    {
        values.apply(value_table);
        count.apply(value_table.getSize());
    }

private:
    Uniform
        values,
        count;
};

}
}
