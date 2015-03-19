#pragma once

#include <cmath>
#include <cstdlib>

namespace gengine
{

template<class T>
struct Range
{
    Range() = default;

    Range(const T & min, const T & max) : minimum(min), maximum(max)
    {
    }

    T getRandom() const
    {
        return minimum + (maximum - minimum) * (std::rand()/ static_cast<float>(RAND_MAX));
    }

    void set(const T & min, const T & max)
    {
        minimum = min;
        maximum = max;
    }

    static void fill(lua_State * state, Range<T> & result, int position = -1)
    {
        lua_rawgeti(state, position, 1);
        script::fill(state, result.minimum, -1);
        lua_pop(state, 1);

        lua_rawgeti(state, position, 2);
        script::fill(state, result.maximum, -1);
        lua_pop(state, 1);
    }

    T
        minimum,
        maximum;
};

}
