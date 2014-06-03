Grid = {}

Grid.__call = function(d, w, h)
    local o = {}
    setmetatable(o, o)
    o.__index = Grid
    o.tiles = {}
    o.width = w
    o.height = h
    o.movingTiles = 0
    return o
end

setmetatable(Grid,Grid)

function Grid:setTile(i, j, t)
    if self.tiles[i] == nil then
        self.tiles[i] = {}
    end

    self.tiles[i][j] = t
    t.x = i
    t.y = j

    t.tile:setGridPosition(i,j)
end

function Grid:moveTiles(i, j, d, ntile)
    if self.movingTiles > 0 then
        ntile:remove()
        return
    end

    if not i then
        for i=0,8 do
            if self.tiles[i] and self.tiles[i][j] then
                self.tiles[i][j].tile:moveTo(i+d,j)
                self.movingTiles = self.movingTiles + 1
            end
        end
        if d > 0 then
            self:setTile(-1,j,ntile)
            ntile.tile:moveTo(0,j)
        else
            self:setTile(9,j,ntile)
            ntile.tile:moveTo(8,j)
        end
    elseif not j then
        for j=0,8 do
            if self.tiles[i] and self.tiles[i][j] then
                self.tiles[i][j].tile:moveTo(i,j+d)
                self.movingTiles = self.movingTiles + 1
            end
        end
        if d > 0 then
            self:setTile(i,-1,ntile)
            ntile.tile:moveTo(i,0)
        else
            self:setTile(i,9,ntile)
            ntile.tile:moveTo(i,8)
        end
    end
end

function Grid:onTileArrived(tile, i, j)
    local width = self.width
    local height = self.height
    if i >= 0 and i < width and j >= 0 and j < height then
        self:setTile(i, j, tile)
    else
        tile:remove()
    end

    self.movingTiles = self.movingTiles - 1
end
