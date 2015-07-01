#pragma once

#include "primitives.h"
#include "map.h"
#include "graphics_texture.h"
#include "script.h"
#include "manager.h"
#include <string>

namespace gengine
{
namespace graphics
{

class TextureManager : public Manager<Texture>
{

public:
    TextureManager() = default;

    MANAGER_DECLARE(TextureManager);

    static SCRIPT_FUNCTION(createFromDirectory);

    static void simplifyName(char *result, const char *input);

private:
    virtual bool internalCreate(Texture * texture, script::State state, const int parameter_position) override;
    virtual void internalGetName(char * name, const char * arg) override;
    virtual void internalInit() override;
    virtual void internalFinalize() override;

    static void internalLuaRegister(script::State state);
};

}
}
