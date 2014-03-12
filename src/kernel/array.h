#pragma once

#include <vector>

namespace gengine
{

template<typename T>
class Array
{
public:
    void add(const T & t)
    {
        array.push_back(t);
    }

    T & operator[](const int index)
    {
        return array[index];
    }

    const T & operator[](const int index) const
    {
        return array[index];
    }
protected:
    std::vector<T> array;
};

}