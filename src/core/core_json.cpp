#include "core_json.h"

namespace gengine
{
namespace core
{

Json::Json()
    :
    jvalue(nullptr),
    itOwnsMemory(false)
{
}

Json::Json(jsonxx::Value * _value)
    :
    jvalue(_value),
    itOwnsMemory(false)
{
}

Json::~Json()
{
    if(itOwnsMemory)
    {
        delete jvalue;
    }
}

Json Json::operator[](const char *name) const
{
    return jvalue->object_value_->kv_map().at(name);
}

Json Json::operator[](const int index) const
{
    return jvalue->array_value_->values().at(index);
}

void Json::parse(const std::string & str)
{
    jvalue = new jsonxx::Value();
    itOwnsMemory = true;

    jvalue->parse(str);
}

void Json::parse(std::istream & istream)
{
    jvalue = new jsonxx::Value();
    itOwnsMemory = true;

    jvalue->parse(istream);
}

}
}
