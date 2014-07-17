
ComponentTile = {}

stateMachine(ComponentTile)

function ComponentTile:init()
    self.time = 0
    self.moveDuration = 0.2
    self.moving = false
    self:changeState("none")
end

function ComponentTile:insert()
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
    if self.state == "none" then
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
        self:changeState("moving")
    end
end

function ComponentTile:rotate()
    if self.state == "none" then
        self.fromRotation = self.entity.rotation
        self.time = 0
        self.toRotation = self.fromRotation - 3.141592/2
        self:changeState("rotating")
    end
end

function ComponentTile:onMouseEnter()
    local sprite = self.entity.sprite
    sprite.color = {x=0,y=1,z=0,w=1}
end

function ComponentTile:onMouseExit()
    self.entity.sprite.color = {x=1,y=1,z=1,w=1}
end

function ComponentTile:onMouseJustDown()
    self:rotate()
end

function ComponentTile:update(dt)
    self:updateState(dt)
end

function ComponentTile.onStateUpdate:moving(dt)
    self.time = self.time + dt

    if self.time >= self.moveDuration then
        self.time = self.moveDuration
        local i,j = self.target[1], self.target[2]
        self.game.grid:onTileArrived(self.entity, i, j)

        self:changeState("none")
    end

    local p = self.entity.position
    local from = self.from
    local target = self.targetPos
    local f = self.time / self.moveDuration

    p.x = from.x + (target.x - from.x) * f
    p.y = from.y + (target.y - from.y) * f
end

function ComponentTile.onStateEnter:rotating()
    self.entity.sprite.color = {x=0,y=1,z=0,w=1}
end

function ComponentTile.onStateUpdate:rotating(dt)
    self.time = self.time + dt

    if self.time >= self.moveDuration then
        self.time = self.moveDuration

        if self.entity.rotation < 0 then
            self.entity.rotation = self.entity.rotation + 3.141592 * 2
        end

        self:changeState("none")
    end

    local p = self.entity.position
    local from = self.fromRotation
    local target = self.toRotation
    local f = self.time / self.moveDuration

    self.entity.rotation = from + (target - from) * f
end

function ComponentTile.onStateExit:rotating()
    self.entity.sprite.color = {x=1,y=1,z=1,w=1}

    self.entity.path:findPath({self.entity}, self.entity)
end
