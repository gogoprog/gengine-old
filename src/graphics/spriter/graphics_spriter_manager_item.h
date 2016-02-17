#pragma once

#include "primitives.h"
#include "script.h"
#include "array.h"
#include "pointer.h"
#include "vector2.h"
#include "map.h"
#include "graphics_texture.h"
#include "graphics_spriter.h"
#include "graphics_sprite_group.h"
#include "transform.h"
#include <string>

namespace gengine
{
namespace graphics
{

class SpriterManagerItem
{
    friend class SpriterManager;

public:
    void init();
    void finalize();
    void fill(SpriteGroup & group, const SpriterMainlineKey & mlk, const Pointer<const SpriterCharacterMap> character_map) const;
    void update(SpriteGroup & group, const SpriterMainlineKey & mlk, const float time, const Pointer<const SpriterCharacterMap> character_map, const Vector2 & scale) const;
    void getBoneTransform(math::Transform & result, const SpriterMainlineKey & mlk, const float time, const uint bone_index) const;

    inline float getDuration() const
    {
        return duration;
    }

    inline bool isLooping() const
    {
        return animation->looping;
    }

    inline const SpriterEntity & getEntity() const
    {
        return * entity;
    }

    inline const SpriterAnimation & getAnimation() const
    {
        return * animation;
    }

private:
    Pointer<const SpriterEntity>
        entity;
    Pointer<const SpriterAnimation>
        animation;
    mutable Map<std::string, Pointer<const Texture>>
        textureCacheMap;
    float
        duration;
};

}
}
