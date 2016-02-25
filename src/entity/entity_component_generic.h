#pragma once

#include "script.h"
#include "script_lua.h"
#include "entity_macros.h"
#include "entity_component.h"
#include <Urho3D/Engine/Engine.h>

namespace gengine
{
namespace entity
{

template<class C>
class ComponentGeneric : public Component
{
public:
    ComponentGeneric();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE(ComponentGeneric);

private:
    Urho3D::SharedPtr<C>
        urhoComponent;

};

}
}

#include "entity_system.h"

namespace gengine
{
namespace entity
{

template<class C>
ComponentGeneric<C>::ComponentGeneric()
    :
    Component()
{
}

template<class C>
void ComponentGeneric<C>::init()
{
    urhoComponent = entity->getNode().CreateComponent<C>();
}

template<class C>
void ComponentGeneric<C>::insert()
{
}

template<class C>
void ComponentGeneric<C>::update(const float /*dt*/)
{
}

template<class C>
void ComponentGeneric<C>::remove()
{
}

template<class C>
SCRIPT_CLASS_FUNCTION(ComponentGeneric<C>, index)
{
    SCRIPT_GET_SELF(ComponentGeneric<C>);
    const char * name = lua_tostring(state, 2);
    getterMap[name](state, self);
    return 1;
}

template<class C>
SCRIPT_CLASS_FUNCTION(ComponentGeneric<C>, create)
{
    return System::getInstance().createComponent<ComponentGeneric<C>>(state);
}

template<class C>
uint
    ComponentGeneric<C>::metaTableRef;

template<class C>
ENTITY_GETTER_MAP_TYPE(ComponentGeneric<C>)
    ComponentGeneric<C>::getterMap;

template<class C>
SCRIPT_CLASS_REGISTERER(ComponentGeneric<C>)
{
}

template<class C>
ENTITY_COMPONENT_SETTERS(ComponentGeneric<C>)
{
    tolua_pushusertype(state, (void*)self.urhoComponent, C::GetTypeNameStatic().CString());
    lua_pushvalue(state, 3);
    lua_setfield(state, -2, key);
    lua_pop(state, 1);
}
ENTITY_COMPONENT_END()

}
}
