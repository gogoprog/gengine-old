dofile('component_tile.lua')

Game = {}

Game.__call = function()
    local o = {}
    setmetatable(o, o)
    o.__index = Game
    o.tiles = {}
    o.origin = { -256, -256 }
    o.tileSize = 64
    return o
end

setmetatable(Game,Game)

function Game:load()
    entity.registerCustomComponent(ComponentTile)

    for i=0,2 do
        graphics.texture.create("data/tile" .. i .. ".png")
    end

    for j=0,8 do
        for i=0,8 do
            local e = self:createTile()
            e.tile:setGridPosition(i,j)

            e.rotation = math.random(1,4) * 3.14/2

            if self.tiles[i] == nil then
                self.tiles[i] = {}
            end

            self.tiles[i][j] = e
        end
    end
end

function Game:createTile()
    local e
    e = entity.create()

    e:addComponent(
        ComponentSprite(),
        {
            texture = graphics.texture.get("tile" .. math.random(0,2)),
            extent = { x=64, y=64 },
            layer = 0
        },
        "sprite"
        )

    e:addComponent(
        ComponentTile(),
        {
            game = self
        },
        "tile"
        )

    e:insert()
    table.insert(self.tiles, e)

    return e
end

function Game:update(dt)
    if input.mouse:isJustDown(1) then
        for i=0,8 do
            self.tiles[i][6].tile:moveTo(i+1,6)
        end
    end
end