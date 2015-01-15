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

    void remove(const K & key)
    {
        data.erase(key);
    }

    V & operator[](const K & key)
    {
        return data[key];
    }

    const V & operator[](const K & key) const
    {
        return data.at(key);
    }

    bool find(V & result, const K & k) const
    {
        typename std::map<K,V>::const_iterator it;

        it = data.find(k);

        if(it != data.end())
        {
            result = it->second;
            return true;
        }

        return false;
    }

    bool contains(const K & k) const
    {
        return data.find(k) != data.end();
    }

    void clear()
    {
        data.clear();
    }

    uint getSize() const
    {
        return data.size();
    }

    typedef typename std::map<K,V>::iterator iterator;
    typedef typename std::map<K,V>::const_iterator const_iterator;
    iterator begin() { return data.begin(); }
    const_iterator begin() const { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator end() const { return data.end(); }

protected:
    std::map<K,V> data;
};

}
