
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
            self.game:setTile(i, j, self.entity)
            print("ok arrived")
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

    e.position.x = self.game.origin[1] + i * self.game.tileSize
    e.position.y = self.game.origin[2] + j * self.game.tileSize
end

function ComponentTile:moveTo(i,j)
    if not self.moving then
        self.targetPos = {
            x = self.game.origin[1] + i * self.game.tileSize,
            y = self.game.origin[2] + j * self.game.tileSize
        }

        self.target = { i, j }

        self.from = {
            x = self.entity.position.x,
            y = self.entity.position.y
        }

        self.moving = true
        self.time = 0
    else
        print("new target " .. i .. ", " .. j )

         i,j = self.target[1], self.target[2]

        print("i am moving " .. self.time .. " " .. i .. ", " .. j )
    end
end