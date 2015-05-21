#include "graphics_spriter_manager_item.h"

#include "graphics_texture_manager.h"

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
    uint sprite_count = mlk.objectKeys.getSize();
    auto sprites = group.getSprites();
    group.setActiveCount(sprite_count);

    for(uint i=0; i<sprite_count; ++i)
    {
        auto & item = mlk.objectKeys[i];

        if ( sprites[i].isNull() )
        {
            sprites[i] = new Sprite();
        }

        auto & sprite = * sprites[i];
        auto & asset = * item.timelineKey->asset;
        std::string texture_name;

        texture_name = character_map ? character_map->assetMap[& asset]->name : asset.name;

        if(textureCacheMap.contains(texture_name))
        {
            sprite.setTexture(* textureCacheMap[texture_name]);
        }
        else
        {
            auto texture = TextureManager::getInstance().getItem(texture_name.c_str());
            textureCacheMap.add(texture, texture_name);
        }

        sprite.setUvScale( Vector2::one );
        sprite.setUvOffset( Vector2::zero );
    }
}

void SpriterManagerItem::update(SpriteGroup & group, const SpriterMainlineKey & mlk, const float time, const Pointer<const SpriterCharacterMap> character_map) const
{

}

}
}
