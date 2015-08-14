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
        return function(filename)
            local result = {}
            local path = filename:match("(.*/)")
            local file = dofile(filename)
            local indexToTileSet = {}

            if file then
                for k, ts in ipairs(file.tilesets) do
                    local texture = gengine.graphics.texture.create(path .. ts.image)
                    ts.atlas = gengine.graphics.atlas.create(ts.name, texture, ts.imagewidth / ts.tilewidth,  ts.imageheight / ts.tileheight)
                    local count = (ts.imagewidth / ts.tilewidth) * (ts.imageheight / ts.tileheight)
                    for i=1,count do
                        table.insert(indexToTileSet, k)
                    end
                end

                for l, layer in ipairs(file.layers) do
                    for k, v in ipairs(layer.data) do
                        if v ~= 0 then
                            local e = gengine.entity.create()
                            local x = (k-1) % layer.width
                            local y = layer.height - math.floor((k-1) / layer.width)
                            local ts = file.tilesets[indexToTileSet[v]]

                            e:addComponent(
                                ComponentSprite(),
                                {
                                    atlas = gengine.graphics.atlas.get("crates"),
                                    atlasItem = v - ts.firstgid,
                                    extent = vector2(file.tilewidth, file.tileheight),
                                    layer = l
                                }
                                )

                            e.position.x = x * file.tilewidth
                            e.position.y = y * file.tileheight

                            table.insert(result, e)
                        end
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
