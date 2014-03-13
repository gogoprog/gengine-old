#pragma once

#include "primitives.h"

namespace gengine
{
namespace graphics
{

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();
    void init();
    void setData(const ushort * indices, const uint count);
    void apply();

private:
    uint id;
};

}
}
