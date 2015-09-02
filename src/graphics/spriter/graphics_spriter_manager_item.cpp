#include "graphics_spriter_manager_item.h"

#include "graphics_texture_manager.h"

namespace gengine
{
namespace graphics
{

void SpriterManagerItem::init()
{
    if(animation)
    {
        duration = animation->length / 1000.0f;
    }
}

void SpriterManagerItem::finalize()
{

}

void SpriterManagerItem::fill(SpriteGroup & group, const SpriterMainlineKey & mlk, const Pointer<const SpriterCharacterMap> character_map) const
{
    uint sprite_count = mlk.objectKeys.getSize();
    auto & sprites = group.getSprites();
    group.setActiveCount(sprite_count);

    if(sprites.getSize() < sprite_count)
    {
        sprites.setSize(sprite_count);
    }

    for(uint i=0; i<sprite_count; ++i)
    {
        auto & item = mlk.objectKeys[i];

        if(sprites[i].isNull())
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
            sprite.setTexture(*texture);
        }

        sprite.setUvScale( Vector2::one );
        sprite.setUvOffset( Vector2::zero );
    }
}

void SpriterManagerItem::update(SpriteGroup & group, const SpriterMainlineKey & mlk, const float time, const Pointer<const SpriterCharacterMap> character_map, const Vector2 & scale) const
{
    Vector2 extent, pivot_to_center;
    SpriterTransform transform;
    uint time_integer = uint(time * 1000.0f);
    auto & sprites = group.getSprites();

    for(uint i=0; i<mlk.objectKeys.getSize(); ++i)
    {
        const auto & item = mlk.objectKeys[i];
        auto & sprite = * sprites[i];
        auto & asset = (!character_map.isNull() ? *character_map->assetMap[item.timelineKey->asset] : *item.timelineKey->asset);

        item.fillTransform(transform, time_integer, true);

        extent = Vector2(float(asset.width), float(asset.height)) * transform.scale * scale;

        sprite.setExtent(extent);

        pivot_to_center = extent * transform.pivot;

        sprite.setPosition(transform.position * scale - Vector2::getRotated(pivot_to_center, transform.angle));

        sprite.setRotation(transform.angle);

        sprite.getColor().w = transform.alpha;
    }
}

}
}
