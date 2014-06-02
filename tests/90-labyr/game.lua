dofile('component_tile.lua')
dofile('component_placer.lua')

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
    entity.registerCustomComponent(ComponentPlacer)

    for i=0,2 do
        graphics.texture.create("data/tile" .. i .. ".png")
    end

    for j=0,8 do
        for i=0,8 do
            local e = self:createTile()
            e.tile:setGridPosition(i,j)

            e.rotation = math.random(1,4) * 3.14/2

            self:setTile(i,j,e)
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
    table.insert(self.tiles, e)

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

    return e
end

function Game:update(dt)

end

function Game:moveTiles(i,j,d)
    if not i then
        for i=0,8 do
            if self.tiles[i] and self.tiles[i][j] then
                self.tiles[i][j].tile:moveTo(i+d,j)
            else
                print("notile " .. i .. ", " .. j)
            end
        end
        if d > 0 then
            self.tiles[0][j] = nil
        else
            self.tiles[8][j] = nil
        end
    elseif not j then
        for j=0,8 do
            if self.tiles[i] and self.tiles[i][j] then
                self.tiles[i][j].tile:moveTo(i,j+d)
            else
                print("notile")
            end
        end
        if d > 0 then
            self.tiles[i][0] = nil
        else
            self.tiles[i][8] = nil
        end
    end
end

function Game:setTile(i,j,e)
    if self.tiles[i] == nil then
        self.tiles[i] = {}
    end

    self.tiles[i][j] = e
    e.x = i
    e.y = j
end