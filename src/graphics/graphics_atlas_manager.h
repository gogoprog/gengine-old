#pragma once

#include "primitives.h"
#include "map.h"
#include "script.h"
#include "manager.h"
#include <string>

namespace gengine
{
namespace graphics
{

class Atlas;

class AtlasManager : public Manager<Atlas>
{

public:
    AtlasManager() = default;

    MANAGER_DECLARE(AtlasManager);

private:
    virtual bool internalCreate(Atlas * atlas, script::State state) override;
    virtual void internalGetName(char * name, const char * arg) override;
};

}
}
