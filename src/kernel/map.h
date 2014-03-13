#pragma once

#include <map>

namespace gengine
{

template<typename K, typename V>
class Map
{
public:
    void add(const V & v, const K & key)
    {
        data[key] = v;
    }

    V & operator[](const K & key)
    {
        return data[key];
    }

    const V & operator[](const K & key) const
    {
        return data[key];
    }

protected:
    std::map<K,V> data;
};

}
