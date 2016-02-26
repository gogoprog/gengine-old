#pragma once

#include "primitives.h"
#include "array.h"
#include "maths.h"
#include "script.h"
#include "debug.h"
#include "pointer.h"

namespace gengine
{
namespace entity
{
class Entity;

class Component
{
    friend class System;

public:
    Component() = default;
    virtual ~Component() = default;

    Component(Component &) = delete;
    Component & operator=(Component &) = delete;

    virtual void init();
    virtual void finalize();
    virtual void insert();
    virtual void update(const float dt);
    virtual void remove();

    void setEntity(Entity & _entity) { entity = & _entity; }

protected:
    Pointer<Entity>
        entity;
};
}
}
