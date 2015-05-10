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

    void parse(const std::string & str);
    void parse(std::istream & istream);

    template<typename T>
    const T& value() const
    {
        return jvalue->get<T>();
    }

    template<typename T>
    bool is() const
    {
        return jvalue->is<T>();
    }

private:
    jsonxx::Value
        * jvalue;
    bool
        itOwnsMemory;
};


}
}
