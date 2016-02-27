#pragma once

#include "primitives.h"
#include "array.h"
#include "maths.h"
#include "script.h"
#include "debug.h"
#include <Urho3D/Scene/Node.h>

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
    bool drivesTransform() const;

    void addComponent(Component & component);

    void init();
    void finalize();
    void insert();
    void remove();
    void update(const float dt);

    Urho3D::Node & getNode() { return *node; }

private:
    Array<Component*>
        components;
    int
        ref;
    bool
        itIsInserted;
    Urho3D::SharedPtr<Urho3D::Node>
        node;
};
}
}
