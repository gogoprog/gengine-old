#pragma once

#include "primitives.h"
#include "array.h"
#include "vector2.h"
#include "script.h"
#include "debug.h"

namespace gengine
{
namespace entity
{
    class Entity
    {
        friend class System;

    public:
        Entity() = default;
        ~Entity() = default;

        inline int getRef() const { return ref; }

    private:
        Array<int>
            componentsRefs;
        int
            ref;
    };
}
}
