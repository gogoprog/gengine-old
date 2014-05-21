
ComponentPlacer = {}

function ComponentPlacer:init()
end

function ComponentPlacer:insert()
end

function ComponentPlacer:update(dt)

end

function ComponentPlacer:remove()
end

function ComponentPlacer:onMouseEnter()
    self.entity.sprite.color = {x=0,y=1,z=0,w=1}
end

function ComponentPlacer:onMouseExit()
    self.entity.sprite.color = {x=1,y=1,z=1,w=1}
end

function ComponentPlacer:onMouseJustDown()
    self.entity.sprite.color = {x=1,y=0,z=0,w=1}

    self.game:moveTiles(self.col, self.row, self.sens)
end