#include "graphics_spriter_manager.h"

#include "debug.h"
#include "core_json.h"
#include <cstring>
#include <iostream>
#include <fstream> 

namespace gengine
{
namespace graphics
{

SCRIPT_CLASS_FUNCTION(SpriterManager, loadFile)
{
    const char * path = lua_tostring(state, 1);

    std::filebuf fb;

    if (fb.open (path, std::ios::in))
    {
        core::Json json;
        std::istream istream(&fb);

        if(json.parse(istream))
        {
            const core::Json
                & entity_json = json["entity"],
                & folder_json = json["folder"];

            for(uint i=0; i<entity_json.getItemCount();++i)
            {
                const core::Json
                    & current_entity_json = entity_json[i],
                    & animation_json = current_entity_json[ "animation" ],
                    & character_map_json = current_entity_json[ "character_map" ];

                geLog(current_entity_json["name"].value<core::Json::String>());
            }
        }
    }

    return 0;
}

bool SpriterManager::internalCreate(SpriterAnimation * animation, script::State state, const int parameter_position)
{
    return false;
}

void SpriterManager::internalGetName(char * result, const char * arg)
{
    strcpy(result, arg);
}

void SpriterManager::internalLuaRegister(script::State state)
{
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(SpriterManager, loadFile);
}

}
}
