Grid = {}

Grid.__call = function(d, w, h, ts)
    local o = {}
    setmetatable(o, o)
    o.__index = Grid
    o.tiles = {}
    o.width = w
    o.height = h
    o.movingTiles = 0
    o.origin = {
        ts * ( w - 1 ) * -0.5,
        ts * ( h - 1 ) * -0.5
        }
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
        entity.destroy(ntile)
        return false
    end

    local w = self.width -1
    local h = self.height -1

    if not i then
        for i=0,w do
            if self.tiles[i] and self.tiles[i][j] then
                self.tiles[i][j].tile:moveTo(i+d,j)
                self.movingTiles = self.movingTiles + 1
            end
        end
        if d > 0 then
            self:setTile(-1,j,ntile)
            ntile.tile:moveTo(0,j)
        else
            self:setTile(w + 1,j,ntile)
            ntile.tile:moveTo(w,j)
        end
        ntile:insert()
        self.movingTiles = self.movingTiles + 1
    elseif not j then
        for j=0,h do
            if self.tiles[i] and self.tiles[i][j] then
                self.tiles[i][j].tile:moveTo(i,j+d)
                self.movingTiles = self.movingTiles + 1
            end
        end
        if d > 0 then
            self:setTile(i,-1,ntile)
            ntile.tile:moveTo(i,0)
        else
            self:setTile(i,h+1,ntile)
            ntile.tile:moveTo(i,h)
        end
        ntile:insert()
        self.movingTiles = self.movingTiles + 1
    end

    return true
end

function Grid:onTileArrived(tile, i, j)
    local width = self.width
    local height = self.height
    if i >= 0 and i < width and j >= 0 and j < height then
        self:setTile(i, j, tile)
    else
        tile:remove()
        entity.destroy(tile)
    end

    self.movingTiles = self.movingTiles - 1
end

function Grid:getTile(i, j)
    if self.tiles[i] then
        return self.tiles[i][j]
    end

    return nil
end
