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

    Json operator[](const char *name) const;
    Json operator[](const uint index) const;

    void parse(const std::string & str);
    void parse(std::istream & istream);

private:
    jsonxx::Value
        * jvalue;
    bool
        itOwnsMemory;
};


}
}
