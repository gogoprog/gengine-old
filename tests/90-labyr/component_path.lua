ComponentPath = {
    gets =  {}
}

function isRoughlyEqual(a,b)
    return a - 0.1 < b and a + 0.1 > b
end

function ComponentPath:init()
    self.isPath = true
end

function ComponentPath:insert()

end

function ComponentPath:remove()
    
end


function ComponentPath:update(dt)
    
end

function ComponentPath:setOriginalDirections(valids)
    self.validDirections = valids
end

function ComponentPath:isValidDirection(i)
    local rot = self.entity.rotation
    local hpi = 3.141592/2

    if isRoughlyEqual(rot, 0) then

    elseif isRoughlyEqual(rot, 1 * hpi) then
        i = i + 1
    elseif isRoughlyEqual(rot, 2 * hpi) then
        i = i + 2
    elseif isRoughlyEqual(rot, 3 * hpi) then
        i = i + 3
    end

    i = ( i % 4 ) + 1

    return self.validDirections[i]
end

ComponentPath.gets[1] = function(self)
    local e = self.entity
    return self.game.grid:getTile(e.x, e.y + 1)
end

ComponentPath.gets[2] = function(self)
    local e = self.entity
    return self.game.grid:getTile(e.x - 1, e.y)
end

ComponentPath.gets[3] = function(self)
    local e = self.entity
    return self.game.grid:getTile(e.x, e.y - 1)
end

ComponentPath.gets[4] = function(self)
    local e = self.entity
    return self.game.grid:getTile(e.x + 1, e.y)
end

function ComponentPath:get(direction)
    if self:isValidDirection(direction) then
        print("dir valid")
        return self.gets[direction](self)
    end

    return nil
end

function ComponentPath:findPath(path, previous)
    for d=1,4 do
        local e = self:get(d)

        if e and e ~= previous then
            path = path or {}
            table.insert(path, self.entity)

            print("path:")
            for k,v in ipairs(path) do
                print(path.x .. ", " .. path.y)
            end

            e.path:findPath(path, self.entity)
        end
    end
end