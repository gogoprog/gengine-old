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

    void remove(const T & t)
    {
        typename std::vector<T>::iterator it;
        it = find(array.begin(), array.end(), t);

        if(it != array.end())
        {
            array.erase(it);
        }
    }

    T & operator[](const int index)
    {
        return array[index];
    }

    const T & operator[](const int index) const
    {
        return array[index];
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
