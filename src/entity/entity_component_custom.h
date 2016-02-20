#pragma once

#include "entity_component.h"

namespace gengine
{
namespace entity
{
class ComponentCustom : public Component
{
public:
    ComponentCustom() = default;

    virtual void init();
    virtual void finalize();
    virtual void insert();
    virtual void update(const float dt);
    virtual void remove();

    void setRef(const int _ref) { ref = _ref; }

protected:

    void scriptCall(const char *name);

    int
        ref;
};
}
}
