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
    void finalize();
    void setData(const ushort * indices, const uint _count);
    void draw(const uint _count);
    void draw();

private:
    uint id;
    uint count;
};

}
}
