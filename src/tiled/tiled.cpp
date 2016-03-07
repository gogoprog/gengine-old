#include "tiled.h"

#include "debug.h"

namespace gengine
{
namespace tiled
{

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_DO(
        return function(filename, offset)
            local result = {}
            local mainEntity

            mainEntity = gengine.entity.create()

            mainEntity:addComponent(
                ComponentTileMap2D(),
                {
                    tmxFile = cache:GetResource("TmxFile2D", filename)
                },
                "tileMap"
                )

            table.insert(result, mainEntity)

            for l=0, mainEntity.tileMap.numLayers-1 do
                local layer = mainEntity.tileMap:GetLayer(l)
                for x=0,layer.width - 1 do
                    for y=0,layer.height - 1 do
                        local tile = layer:GetTile(x, y)

                        if tile then
                            local physic

                            if layer:HasProperty("physic") then
                                physic = layer:GetProperty("physic")
                            end

                            if tile:HasProperty("physic") then
                                physic = tile:GetProperty("physic")
                            end

                            if physic then
                                local node = layer:GetTileNode(x, y)
                                local e = gengine.entity.create(node)

                                e:addComponent(
                                    ComponentRigidBody2D(),
                                    {
                                        bodyType = physic == "dynamic" and BT_DYNAMIC or BT_STATIC
                                    }
                                    )

                                e:addComponent(
                                    ComponentCollisionBox2D(),
                                    {
                                        size = Vector2(tile.sprite.rectangle.width, tile.sprite.rectangle.height),
                                        density = 1.0,
                                        friction = 0.0,
                                        restitution = 0.1
                                    }
                                    )

                                table.insert(result, e)
                            end
                        end
                    end
                end

                local func

                if layer:HasProperty("function") then
                    func = layer:GetProperty("function")
                end

                for o=0, layer.numObjects - 1 do
                    if func then
                        local tmo = layer:GetObject(o)
                        local f = loadstring("return " .. func)()
                        f(tmo)
                    end
                end
            end

            return result
        end
    );
    lua_setfield(state, -2, "createEntities");

    lua_setfield(state, -2, "tiled");
}

}
}
