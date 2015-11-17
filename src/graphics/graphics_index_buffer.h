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
    void init(const uint count, const bool use_as_stream);
    void finalize();
    void setData(const ushort * indices, const uint _count, const bool stream = false);
    ushort *map();
    void unMap();
    void draw(const uint _count);

private:
    uint
        id;
    #ifdef EMSCRIPTEN
        ushort
            *data;
        uint
            dataCount;
        bool
            streamUsage;
    #endif
};

}
}
