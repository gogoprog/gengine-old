#pragma once

#include "primitives.h"
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

    void remove(const T & t)
    {
        typename std::vector<T>::iterator it;
        it = find(array.begin(), array.end(), t);

        if(it != array.end())
        {
            array.erase(it);
        }
    }

    void removeAt(const int index)
    {
        array.erase(array.begin() + index);
    }

    void reserve(const int size)
    {
        array.reserve(size);
    }

    void setSize(const int size)
    {
        array.resize(size);
    }

    T & operator[](const int index)
    {
        return array[index];
    }

    const T & operator[](const int index) const
    {
        return array[index];
    }

    T & getLast()
    {
        return array[array.size() - 1];
    }

    uint getSize() const { return array.size(); }

    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin() { return &array[0]; }
    const_iterator begin() const { return &array[0]; }
    iterator end() { return &array[getSize()]; }
    const_iterator end() const { return &array[getSize()]; }

protected:
    std::vector<T> array;
};

}
