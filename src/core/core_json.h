#pragma once

#include "primitives.h"
#include "jsonxx.h"

namespace gengine
{
namespace core
{

class Json
{
public:
    Json();
    Json(jsonxx::Value * _value);
    ~Json();

    typedef jsonxx::Number Number;
    typedef jsonxx::Boolean Boolean;
    typedef jsonxx::String String;
    typedef jsonxx::Null Null;
    typedef jsonxx::Object Object;
    typedef jsonxx::Array Array;

    Json operator[](const char *name) const;
    Json operator[](const int index) const;

    bool has(const char *name) const;

    uint getSize() const;

    bool parse(const std::string & str);
    bool parse(std::istream & istream);

    template<typename T>
    const T& get() const
    {
        return jvalue->get<T>();
    }

    template<typename T>
    bool is() const
    {
        return jvalue->is<T>();
    }

    String getString() const
    {
        return jvalue->get<String>();
    }

    float getFloat() const
    {
        return float(jvalue->get<Number>());
    }

    uint getUint() const
    {
        return uint(jvalue->get<Number>());
    }

    int getInt() const
    {
        return int(jvalue->get<Number>());
    }

    bool getBool() const
    {
        return jvalue->get<Boolean>();
    }

private:
    void reset();

    jsonxx::Value
        * jvalue;
    bool
        itOwnsMemory;
};


}
}
