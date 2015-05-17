#pragma once

#include "primitives.h"
#include "script.h"
#include "array.h"
#include "map.h"
#include "pointer.h"
#include "vector2.h"
#include "core_json.h"
#include <string>

namespace gengine
{
namespace graphics
{

struct SpriterFile;
struct SpriterEntity;
struct SpriterAnimation;

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
    char
        spin;
    Pointer<SpriterAsset>
        asset;
};

struct SpriterMainlineKeyItem
{
    Pointer<SpriterTimelineKey>
        timelineKey,
        nextTimelineKey;
    Pointer<SpriterMainlineKeyItem>
        parent;
};

struct SpriterMainlineKey
{
    void load(const core::Json & json, const SpriterAnimation & animation);

    Array<SpriterTimelineKey>
        keys;
    std::string
        name;
};

struct SpriterTimeline
{
    void load(const core::Json & json, const SpriterFile & file);

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
    Map<Pointer<SpriterAsset>, Pointer<SpriterAsset>>
        assetMap;
};

struct SpriterAnimation
{
    void load(const core::Json & json, const SpriterFile & file, const SpriterEntity & entity);

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
