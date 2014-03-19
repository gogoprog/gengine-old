#pragma once

#include "primitives.h"
#include "array.h"
#include "script.h"
#include "vector2.h"

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
    struct Transform
    {
        Vector2
            position;
        float
            rotation;
    };

    static void pushTransform(lua_State * state, const Transform & transform);

    Array<int>
        refTable;
};

}
}
