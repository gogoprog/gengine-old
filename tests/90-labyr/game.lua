
Game = {}

Game.__call = function()
    local o = {}
    setmetatable(o, o)
    o.__index = Game
    o.tiles = {}
    return o
end

setmetatable(Game,Game)

function Game:load()
    graphics.texture.load("data/tile.png")

    for i=0,8 do
        local e = self:createTile()
        e.position.x = -256 + i * 64
        e.rotation = math.random(1,4) * 3.14/2
    end
end

function Game:createTile()
    local e
    e = entity.create()

    e:addComponent(
        ComponentSprite(),
        {
            texture = graphics.texture.get("tile"),
            extent = { x=64, y=64 },
            layer = 0
        }
        )

    e:insert()
    table.insert(self.tiles, e)

    return e
end