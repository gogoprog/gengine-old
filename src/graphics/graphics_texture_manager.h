#pragma once

#include "primitives.h"
#include "map.h"
#include "graphics_texture.h"
#include "script.h"
#include <string>

namespace gengine
{
namespace graphics
{

class TextureManager
{

public:
    TextureManager() = default;

    void init();
    void finalize();

    SINGLETON(TextureManager);
    static SCRIPT_REGISTERER();
    static SCRIPT_FUNCTION(load);
    static SCRIPT_FUNCTION(get);

private:
    Map<std::string, Texture*>
        textureMap;
};

}
}
