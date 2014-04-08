#pragma once

#include "primitives.h"
#include "map.h"
#include "script.h"
#include <string>

namespace gengine
{
namespace graphics
{

class Atlas;

class AtlasManager
{

public:
    AtlasManager() = default;

    void init();
    void finalize();

    SINGLETON(AtlasManager);
    static SCRIPT_REGISTERER();
    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(get);

private:
    static void getBaseName(char * result, const char * file_path);

    Map<std::string, Atlas*>
        atlasMap;
};

}
}
