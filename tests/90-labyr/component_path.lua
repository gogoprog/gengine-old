ComponentPath = {}

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

function ComponentPath:setOriginalDirections(n,e,s,o)
    self.validDirections = {n,e,s,o}
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