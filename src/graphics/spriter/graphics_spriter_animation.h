#pragma once

#include "primitives.h"
#include "script.h"
#include "array.h"
#include "pointer.h"
#include "vector2.h"
#include <string>

namespace gengine
{
namespace graphics
{

struct SpriterAsset
{
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
    Array<SpriterTimelineKey>
        keys;
    std::string
        name;
};

struct SpriterTimeline
{
    Array<SpriterTimelineKey>
        keys;
    std::string
        name;
};

class SpriterAnimation
{
    friend class SpriterManager;

public:
    void init();
    void finalize();

private:
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

}
}
