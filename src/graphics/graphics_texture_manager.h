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

private:
    virtual bool internalCreate(Texture * texture, script::State state) override;
    virtual void internalGetName(char * name, const char * arg) override;
};

}
}
