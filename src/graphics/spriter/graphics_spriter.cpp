#include "graphics_spriter.h"

#include "debug.h"

namespace gengine
{
namespace graphics
{

void SpriterAsset::load(const core::Json & json)
{
    name = json["name"].getString();

    width = json["width"].getUint();
    height = json["height"].getUint();

    pivot.x = json["pivot_x"].getFloat();
    pivot.y = json["pivot_y"].getFloat();
}

void SpriterCharacterMap::load(const core::Json & json, const SpriterFile & file)
{

}

void SpriterAnimation::load(const core::Json & json, const SpriterFile & file, const SpriterEntity & entity)
{
    const core::Json
        & timeline_json = json["timeline"],
        & mainline_json = json["mainline"]["key"];

    name = json["name"].getString();
    length = json["length"].getUint();

    if(json.has("looping"))
    {
        looping = json["looping"].getBool();
    }
    else
    {
        looping = true;
    }

    timelines.reserve(timeline_json.getSize());
}

void SpriterEntity::load(const core::Json & json, const SpriterFile & file)
{
    const core::Json
        & animation_json = json[ "animation" ],
        & character_map_json = json[ "character_map" ];

    name = json["name"].getString();

    animations.reserve(animation_json.getSize());

    for(uint i=0; i<animation_json.getSize();++i)
    {
        animations.add();
        animations.getLastItem().load(animation_json[i], file, *this);
    }

    characterMaps.reserve(character_map_json.getSize());

    for(uint i=0; i<character_map_json.getSize();++i)
    {
        characterMaps.add();
        characterMaps.getLastItem().load(character_map_json[i], file);
    }
}

void SpriterFile::load(const core::Json & json)
{
    const core::Json
        & entity_json = json["entity"],
        & folder_json = json["folder"];

    allAssets.reserve(folder_json.getSize());

    for(uint i=0; i<folder_json.getSize();++i)
    {
        const core::Json
            & file_json = folder_json[i]["file"];

        allAssets.add();

        Array<SpriterAsset> & assets = allAssets.getLastItem();

        for(uint f=0; f<file_json.getSize(); ++f)
        {
            assets.add();

            SpriterAsset & asset = assets.getLastItem();

            asset.load(file_json[f]);
        }
    }

    entities.reserve(entity_json.getSize());

    for(uint i=0; i<entity_json.getSize();++i)
    {
        entities.add();
        entities.getLastItem().load(entity_json[i], *this);
    }
}

}
}
