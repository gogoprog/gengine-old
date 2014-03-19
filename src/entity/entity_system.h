#pragma once

#include "primitives.h"
#include "array.h"
#include "script.h"

namespace gengine
{
namespace entity
{

class System
{
public:
    SINGLETON(System);

    void init();
    void update(const float dt);

    SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);

private:
    Array<int>
        refTable;
};

}
}
