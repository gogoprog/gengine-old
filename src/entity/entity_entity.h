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
    Entity();
    ~Entity() = default;

    Entity(Entity &) = delete;
    Entity & operator=(Entity &) = delete;

    inline int getRef() const { return ref; }
    inline bool isInserted() const { return itIsInserted; }

    void addComponent(Component & component);

    void insert();
    void remove();
    void update(const float dt);

    math::Transform
        transform;

private:
    Array<Component*>
        components;
    int
        ref;
    bool
        itIsInserted;
};
}
}
