
ComponentTile = {}

function ComponentTile:init()
    self.time = 0
    self.moveDuration = 1.0
    self.moving = false
end

function ComponentTile:insert()
end

function ComponentTile:update(dt)
    if self.moving then

        if self.time >= self.moveDuration then
            self.time = self.moveDuration
            self.moving = false
        end

        local p = self.entity.position
        local from = self.from
        local target = self.target
        local f = self.time / self.moveDuration

        p.x = from.x + (target.x - from.x) * f
        p.y = from.y + (target.y - from.y) * f

        self.time = self.time + dt
    end
end

function ComponentTile:remove()
end

function ComponentTile:setGridPosition(i,j)
    local e = self.entity

    e.position.x = self.game.origin[1] + i * self.game.tileSize
    e.position.y = self.game.origin[2] + j * self.game.tileSize
end

function ComponentTile:moveTo(i,j)
    self.target = {
        x = self.game.origin[1] + i * self.game.tileSize,
        y = self.game.origin[2] + j * self.game.tileSize
    }

    self.from = {
        x = self.entity.position.x,
        y = self.entity.position.y
    }

    self.moving = true
end