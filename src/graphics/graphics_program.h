#pragma once

#include "primitives.h"

namespace gengine
{
namespace graphics
{

class Shader;

class Program
{
public:
    void init();
    void attachShader(const Shader & shader);
    void link();
private:
    uint id;
};

}
}
