dofile('component_tile.lua')
dofile('component_placer.lua')
dofile('component_path.lua')
dofile('grid.lua')
dofile('tiles.lua')

Game = {}

Game.__call = function()
    local o = {}
    setmetatable(o, o)
    o.__index = Game
    o.placers = {}
    o.tileSize = 32
    o.grid = Grid(9, 9, o.tileSize)
    o.grid.game = o
    return o
end

setmetatable(Game,Game)

stateMachine(Game)

function Game:load()
    entity.registerCustomComponent(ComponentTile)
    entity.registerCustomComponent(ComponentPlacer)
    entity.registerCustomComponent(ComponentPath)

    for i=0,2 do
        graphics.texture.create("data/tile" .. i .. ".png")
    end

    local w = self.grid.width -1
    local h = self.grid.height -1

    for j=0,h do
        for i=0,w do
            local e = self:createTile()

            self.grid:setTile(i,j,e)

            e:insert()
        end
    end

    local i = -1
    for j=0,h do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.row = j
        e.placer.sens = 1
        e.placer.game = self
    end

    i = w + 1
    for j=0,h do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.row = j
        e.placer.sens = -1
    end

    local j = -1
    for i=0,w do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.col = i
        e.placer.sens = 1
    end

    j = h + 1
    for i=0,w do
        local e = self:createPlacer()
        e.tile:setGridPosition(i,j)
        e.placer.col = i
        e.placer.sens = -1
    end

    self.nextPiece = math.random(1,#Tiles)
end

function Game:createTile(_t)
    local e
    local t = _t == nil and math.random(1, #Tiles) or _t

    local definition = Tiles[t]

    e = entity.create()

    e:addComponent(
        ComponentSprite(),
        {
            texture = graphics.texture.get(definition.file),
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

    e:addComponent(
        ComponentPath(),
        {
            game = self
        },
        "path"
        )

    e:addComponent(
        ComponentMouseable(),
        {
            extent = { x=self.tileSize, y=self.tileSize }
        }
        )

    e.path:setOriginalDirections(definition.validDirections)
    e.rotation = definition.rotation or 0

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
    if self.grid:moveTiles(i, j, d, self:createTile(self.nextPiece)) then
        self.nextPiece = math.random(1,#Tiles)
    end
end