#pragma once

#include "primitives.h"
#include "array.h"
#include "vector2.h"
#include "script.h"
#include "debug.h"
#include "transform.h"

namespace gengine
{
namespace entity
{
class Component;

class Entity
{
    friend class System;

public:
    Entity() = default;
    ~Entity() = default;

    inline int getRef() const { return ref; }

    math::Transform
        tranform;

private:
    Array<Component*>
        componentsRefs;
    int
        ref;
};
}
}
