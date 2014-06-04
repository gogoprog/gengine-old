dofile('component_tile.lua')
dofile('component_placer.lua')
dofile('grid.lua')

Game = {}

Game.__call = function()
    local o = {}
    setmetatable(o, o)
    o.__index = Game
    o.placers = {}
    o.grid = Grid(9, 9)
    o.grid.game = o
    o.origin = { -256, -256 }
    o.tileSize = 64
    return o
end

setmetatable(Game,Game)

function Game:load()
    entity.registerCustomComponent(ComponentTile)
    entity.registerCustomComponent(ComponentPlacer)

    for i=0,2 do
        graphics.texture.create("data/tile" .. i .. ".png")
    end

    for j=0,8 do
        for i=0,8 do
            local e = self:createTile()

            e.rotation = math.random(1,4) * 3.14/2

            self.grid:setTile(i,j,e)
        end
    end

    local i = -1
    for j=0,8 do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.row = j
        e.placer.sens = 1
    end

    i = 9
    for j=0,8 do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.row = j
        e.placer.sens = -1
    end

    local j = -1
    for i=0,8 do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.col = i
        e.placer.sens = 1
    end

    j = 9
    for i=0,8 do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.col = i
        e.placer.sens = -1
    end
end

function Game:createTile()
    local e
    e = entity.create()

    e:addComponent(
        ComponentSprite(),
        {
            texture = graphics.texture.get("tile" .. math.random(0,2)),
            extent = { x=self.tileSize, y=self.tileSize },
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

    return e
end

function Game:createPlacer()
    local e
    e = entity.create()

    e:addComponent(
        ComponentSprite(),
        {
            texture = graphics.texture.get("tile0"),
            extent = { x=self.tileSize, y=self.tileSize },
            layer = 0
        },
        "sprite"
        )

    e:addComponent(
        ComponentMouseable(),
        {
            extent = { x=self.tileSize, y=self.tileSize }
        }
        )

    e:addComponent(
        ComponentPlacer(),
        {
            game = self
        },
        "placer"
        )

    e:addComponent(
        ComponentTile(),
        {
            game = self
        },
        "tile"
        )

    e:insert()

    table.insert(self.placers, e)

    return e
end

function Game:update(dt)
    if input.mouse:isDown(3) then
       self:moveTiles(0, nil, 1)
    end
end


function Game:moveTiles(i, j, d)
    self.grid:moveTiles(i, j, d, self:createTile())
end