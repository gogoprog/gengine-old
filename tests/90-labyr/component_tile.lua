
ComponentTile = {}

function ComponentTile:init()
    self.time = 0
    self.moveDuration = 0.2
    self.moving = false
end

function ComponentTile:insert()
end

function ComponentTile:update(dt)
    if self.moving then

        self.time = self.time + dt

        if self.time >= self.moveDuration then
            self.time = self.moveDuration
            self.moving = false
            local i,j = self.target[1], self.target[2]
            self.game.grid:onTileArrived(self.entity, i, j)
        end

        local p = self.entity.position
        local from = self.from
        local target = self.targetPos
        local f = self.time / self.moveDuration

        p.x = from.x + (target.x - from.x) * f
        p.y = from.y + (target.y - from.y) * f
    end
end

function ComponentTile:remove()
end

function ComponentTile:setGridPosition(i,j)
    local e = self.entity
    local game = self.game
    local origin = game.grid.origin

    e.position.x = origin[1] + i * game.tileSize
    e.position.y = origin[2] + j * game.tileSize
end

function ComponentTile:moveTo(i,j)
    if not self.moving then
        local game = self.game
        local origin = game.grid.origin

        self.targetPos = {
            x = origin[1] + i * game.tileSize,
            y = origin[2] + j * game.tileSize
        }

        self.target = { i, j }

        self.from = {
            x = self.entity.position.x,
            y = self.entity.position.y
        }

        self.moving = true
        self.time = 0
    end
end
