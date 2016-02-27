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
    Component();
    virtual ~Component() = default;

    Component(Component &) = delete;
    Component & operator=(Component &) = delete;

    bool drivesTransform() const { return itDrivesTransform; }

    virtual void init();
    virtual void finalize();
    virtual void insert();
    virtual void update(const float dt);
    virtual void remove();
    virtual void onPropertySet(const char *name);

    void setEntity(Entity & _entity) { entity = & _entity; }

protected:
    Pointer<Entity>
        entity;
    bool
        itDrivesTransform;
};
}
}
