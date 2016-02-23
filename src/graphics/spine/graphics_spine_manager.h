#pragma once

#include "primitives.h"
#include "map.h"
#include "graphics_spine_manager_item.h"
#include "script.h"
#include "manager.h"
#include <string>

namespace gengine
{
namespace graphics
{

class SpineManager : public Manager<SpineManagerItem>
{

public:
    SpineManager() = default;

    MANAGER_DECLARE(SpineManager);

private:
    virtual SpineManagerItem * internalCreate(script::State state, const int parameter_position) override;
    virtual void internalGetName(char * name, const char * arg) override;

};

}
}
