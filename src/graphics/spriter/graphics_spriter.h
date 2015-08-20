#pragma once

#include "primitives.h"
#include "script.h"
#include "array.h"
#include "map.h"
#include "pointer.h"
#include "vector2.h"
#include "core_json.h"
#include <string>
#include <algorithm>

namespace gengine
{
namespace graphics
{

struct SpriterFile;
struct SpriterEntity;
struct SpriterAnimation;

struct SpriterTransform
{
    Vector2
        position,
        pivot,
        scale;
    float
        angle,
        alpha;
};

struct SpriterAsset
{
    void load(const core::Json & json);

    uint
        width,
        height;
    std::string
        name;
    Vector2
        pivot;
};

struct SpriterTimelineKey
{
    void load(const core::Json & json, const SpriterFile & file);

    float
        angle,
        alpha;
    Vector2
        pivot,
        position,
        scale;
    uint
        time;
    int8
        spin;
    Pointer<const SpriterAsset>
        asset;
};

struct SpriterMainlineKeyItem
{
    void fillTransform(SpriterTransform & transform, const uint time, const bool interpolation) const;

    Pointer<const SpriterTimelineKey>
        timelineKey,
        nextTimelineKey;
    Pointer<const SpriterMainlineKeyItem>
        parent;
    uint
        animationLength;
};

struct SpriterMainlineKey
{
    void load(const core::Json & json, const SpriterAnimation & animation);
    void fill(Array<SpriterMainlineKeyItem> & table, const core::Json & json, const SpriterAnimation & animation);

    Array<SpriterMainlineKeyItem>
        boneKeys,
        objectKeys;
    uint
        time;
};

struct SpriterTimeline
{
    void load(const core::Json & json, const SpriterFile & file);

    const SpriterTimelineKey & get(const uint index, const bool looping) const
    {
        return keys[looping ? (index%keys.getSize()) : (std::min(keys.getSize() - 1, index))];
    }

    Array<SpriterTimelineKey>
        keys;
    std::string
        name;
};

struct SpriterCharacterMap
{
    void load(const core::Json & json, const SpriterFile & file);

    std::string
        name;
    Map<Pointer<const SpriterAsset>, Pointer<const SpriterAsset>>
        assetMap;
};

struct SpriterAnimation
{
    void load(const core::Json & json, const SpriterFile & file, const SpriterEntity & entity);

    const SpriterMainlineKey & getMainlineKey(const float time) const;

    std::string
        name;
    uint
        length;
    bool
        looping;
    Array<SpriterMainlineKey>
        mainlineKeys;
    Array<SpriterTimeline>
        timelines;
};

struct SpriterEntity
{
    void load(const core::Json & json, const SpriterFile & file);

    const SpriterCharacterMap * getCharacterMap(const char *name) const;

    std::string
        name;
    Array<SpriterAnimation>
        animations;
    Array<SpriterCharacterMap>
        characterMaps;
};

struct SpriterFile
{
    void load(const core::Json & json);

    Array<SpriterEntity>
        entities;
    Array<Array<SpriterAsset>>
        allAssets;
};

}
}
