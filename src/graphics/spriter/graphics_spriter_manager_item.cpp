#include "graphics_spriter_manager_item.h"

namespace gengine
{
namespace graphics
{

void SpriterManagerItem::init()
{
    duration = animation->length / 1000.0f;
}

void SpriterManagerItem::finalize()
{

}

void SpriterManagerItem::fill(SpriteGroup & group, const SpriterMainlineKey & mlk, const Pointer<const SpriterCharacterMap> character_map) const
{

}

void SpriterManagerItem::update(SpriteGroup & group, const SpriterMainlineKey & mlk, const float time, const Pointer<const SpriterCharacterMap> character_map) const
{

}

}
}
