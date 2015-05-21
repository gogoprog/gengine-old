#pragma once

#include "primitives.h"

namespace gengine
{

template<typename T>
class Pointer
{
public:
    Pointer()
        :
        value(nullptr)
    {
    }

    Pointer(T * _value)
        :
        value(_value)
    {
    }

    T * operator->() const
    {
        return value;
    }

    T & operator*() const
    {
        return * value;
    }

    operator T*()
    {
        return value;
    }

    operator bool() const
    {
        return value != nullptr;
    }

    bool operator <(const Pointer<T> & other) const
    {
        return value < other.value;
    }

    bool operator ==(const Pointer<T> & other) const
    {
        return value == other.value;
    }

    bool operator !=(const Pointer<T> & other) const
    {
        return value != other.value;
    }

    bool operator !=(T * other) const
    {
        return value != other;
    }

    bool isNull() const { return value == nullptr; }

protected:
    T
        * value;
};

}
