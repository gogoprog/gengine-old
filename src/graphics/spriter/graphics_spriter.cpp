#include "graphics_spriter.h"

#include "debug.h"
#include "maths.h"
#include "graphics_texture_manager.h"

namespace gengine
{
namespace graphics
{

uint getOrDefault(const core::Json & json, const char * key, const uint default_value)
{
    if(json.has(key))
    {
        return json[key].getUint();
    }

    return default_value;
}

int getOrDefault(const core::Json & json, const char * key, const int default_value)
{
    if(json.has(key))
    {
        return json[key].getInt();
    }

    return default_value;
}

float getOrDefault(const core::Json & json, const char * key, const float default_value)
{
    if(json.has(key))
    {
        return json[key].getFloat();
    }

    return default_value;
}

bool getOrDefault(const core::Json & json, const char * key, const bool default_value)
{
    if(json.has(key))
    {
        return json[key].getBool();
    }

    return default_value;
}

void SpriterAsset::load(const core::Json & json)
{
    char corrected_name[128];

    TextureManager::simplifyName(corrected_name, json["name"].getString().c_str());

    name = corrected_name;

    width = json["width"].getUint();
    height = json["height"].getUint();

    pivot.x = json["pivot_x"].getFloat();
    pivot.y = json["pivot_y"].getFloat();
}

void SpriterTimelineKey::load(const core::Json & json, const SpriterFile & file)
{
    if(json.has("object"))
    {
        const core::Json & object = json["object"];

        angle = getOrDefault(object, "angle", 0.0f) / (180.0f / math::pi);
        alpha = getOrDefault(object, "alpha", 1.0f);

        asset = & file.allAssets[object["folder"].getUint()][object["file"].getUint()];

        pivot.x = getOrDefault(object, "pivot_x", asset->pivot.x) - 0.5f;
        pivot.y = getOrDefault(object, "pivot_y", asset->pivot.y) - 0.5f;

        position.x = getOrDefault(object, "x", 0.0f);
        position.y = getOrDefault(object, "y", 0.0f);
        scale.x = getOrDefault(object, "scale_x", 1.0f);
        scale.y = getOrDefault(object, "scale_y", 1.0f);
    }
    else if(json.has("bone"))
    {
        const core::Json & bone = json["bone"];

        angle = getOrDefault(bone, "angle", 0.0f) / (180.0f / math::pi);
        alpha = getOrDefault(bone, "alpha", 1.0f);
        position.x = getOrDefault(bone, "x", 0.0f);
        position.y = getOrDefault(bone, "y", 0.0f);
        scale.x = getOrDefault(bone, "scale_x", 1.0f);
        scale.y = getOrDefault(bone, "scale_y", 1.0f);
    }

    time = getOrDefault(json, "time", 0u);
    spin = getOrDefault(json, "spin", 1);
}

void SpriterMainlineKeyItem::fillTransform(SpriterTransform & transform, const uint time, const bool interpolation) const
{
    const SpriterTimelineKey & tk = * timelineKey;
    Vector2 position, scale, pivot;
    float angle, alpha;

    if(!interpolation || timelineKey == nextTimelineKey)
    {
        position = tk.position;
        scale = tk.scale;
        angle = tk.angle;
        pivot = tk.pivot;
        alpha = tk.alpha;
    }
    else
    {
        const SpriterTimelineKey & ntk = * nextTimelineKey;
        int8 spin;
        float delta_angle, factor;

        if(ntk.time > tk.time)
        {
            factor = (time - tk.time) / float(ntk.time - tk.time);
        }
        else
        {
            factor = (time - tk.time) / float(ntk.time + animationLength - tk.time);
        }

        position = math::getLerp(tk.position, ntk.position, factor);
        pivot = math::getLerp(tk.pivot, ntk.pivot, factor);
        scale = math::getLerp(tk.scale, ntk.scale, factor);
        alpha = math::getLerp(tk.alpha, ntk.alpha, factor);

        spin = tk.spin;

        delta_angle = ntk.angle - tk.angle;

        if(spin * delta_angle <= 0)
        {
            delta_angle += spin * math::pi * 2.0f;
            delta_angle *= spin * spin;
        }

        angle = math::getLerp(tk.angle, tk.angle + delta_angle, factor);
    }

    if(parent.isNull())
    {
        transform.position = position;
        transform.pivot = pivot;
        transform.scale = scale;
        transform.angle = angle;
        transform.alpha = alpha;
    }
    else
    {
        parent->fillTransform(transform, time, interpolation);
        transform.position += Vector2::getRotated(position * transform.scale, math::getClosestAngle(transform.angle, 0.0f));
        transform.pivot = pivot;
        transform.scale *= scale;
        transform.angle += angle;
        transform.alpha *= alpha;
    }
}

void SpriterMainlineKey::load(const core::Json & json, const SpriterAnimation & animation)
{
    time = getOrDefault(json, "time", 0u);

    fill(boneKeys, json["bone_ref"], animation);
    fill(objectKeys, json["object_ref"], animation);
}


void SpriterMainlineKey::fill(Array<SpriterMainlineKeyItem> & table, const core::Json & json, const SpriterAnimation & animation)
{
    table.setSize(json.getSize());

    for(uint i=0; i<json.getSize();++i)
    {
        const core::Json
            & item_json = json[i],
            & timeline_json = item_json["timeline"];
        SpriterMainlineKeyItem
            & item = table[i];
        uint timeline, key;

        if(timeline_json.is<core::Json::Number>())
        {
            timeline = timeline_json.getUint();
        }
        else
        {
            timeline = std::stoi(timeline_json.getString());
        }

        key = item_json["key"].getUint();

        item.timelineKey = & animation.timelines[timeline].get(key, animation.looping);
        item.nextTimelineKey = & animation.timelines[timeline].get(key+1, animation.looping);

        if(item_json.has("parent"))
        {
            item.parent = & boneKeys[item_json["parent"].getUint()];
        }

        item.animationLength = animation.length;
    }
}

void SpriterTimeline::load(const core::Json & json, const SpriterFile & file)
{
    const core::Json
        & key_json = json["key"];

    name = json["name"].getString();

    keys.reserve(key_json.getSize());

    for(uint i=0; i<key_json.getSize();++i)
    {
        keys.add();
        keys.getLastItem().load(key_json[i], file);
    }
}

void SpriterCharacterMap::load(const core::Json & json, const SpriterFile & file)
{
    const core::Json
        & map_json = json["map"];

    name = json["name"].getString();

    for(uint i=0; i<map_json.getSize();++i)
    {
        const core::Json
            & item = map_json[i];

        assetMap.add(
            & file.allAssets[item["target_folder"].getUint()][item["target_file"].getUint()],
            & file.allAssets[item["folder"].getUint()][item["file"].getUint()]
            );
    }
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
        if(json["looping"].is<core::Json::Boolean>())
        {
            looping = json["looping"].getBool();
        }
        else
        {
            looping = (json["looping"].getString() == "true");
        }
    }
    else
    {
        looping = true;
    }

    timelines.reserve(timeline_json.getSize());

    for(uint i=0; i<timeline_json.getSize();++i)
    {
        timelines.add();
        timelines.getLastItem().load(timeline_json[i], file);
    }

    mainlineKeys.reserve(mainline_json.getSize());

    for(uint i=0; i<mainline_json.getSize();++i)
    {
        mainlineKeys.add();
        mainlineKeys.getLastItem().load(mainline_json[i], *this);
    }
}

const SpriterMainlineKey & SpriterAnimation::getMainlineKey(const float ftime) const
{
    uint time, index;

    time = uint(ftime * 1000);

    if(looping)
    {
        time %= length;
    }

    for(index=0; index<mainlineKeys.getSize();++index)
    {
        if(time < mainlineKeys[index].time)
        {
            break;
        }
    }

    --index;

    return mainlineKeys[index];
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
