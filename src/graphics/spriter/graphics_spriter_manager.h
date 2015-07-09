#pragma once

#include "primitives.h"
#include "map.h"
#include "graphics_spriter_manager_item.h"
#include "graphics_spriter.h"
#include "script.h"
#include "manager.h"
#include <string>

namespace gengine
{
namespace graphics
{

class SpriterManager : public Manager<SpriterManagerItem>
{

public:
    SpriterManager() = default;

    MANAGER_DECLARE(SpriterManager);

    static SCRIPT_FUNCTION(loadFile);

private:
    virtual bool internalCreate(SpriterManagerItem * item, script::State state, const int parameter_position) override;
    virtual void internalGetName(char * name, const char * arg) override;

    static void internalLuaRegister(script::State state);

    Array<Pointer<SpriterFile>>
        files;
};

}
}
