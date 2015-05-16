#include "graphics_spriter.h"

#include "debug.h"

namespace gengine
{
namespace graphics
{

void SpriterFile::load(const core::Json & json)
{
    const core::Json
        & entity_json = json["entity"],
        & folder_json = json["folder"];


    assets.reserve(folder_json.getSize());

    for(uint i=0; i<folder_json.getSize();++i)
    {

    }

    entities.reserve(entity_json.getSize());

    for(uint i=0; i<entity_json.getSize();++i)
    {
        const core::Json
            & current_entity_json = entity_json[i],
            & animation_json = current_entity_json[ "animation" ],
            & character_map_json = current_entity_json[ "character_map" ];

        geLog(current_entity_json["name"].value<core::Json::String>());

    }
}

}
}
