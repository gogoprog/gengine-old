
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
    local sprite = self.entity.sprite
    local def = Tiles[self.game.nextPiece]
    sprite.color = {x=0,y=1,z=0,w=1}
    sprite.texture = graphics.texture.get(def.file)
    self.entity.rotation = def.rotation
end

function ComponentPlacer:onMouseExit()
    self.entity.sprite.color = {x=1,y=1,z=1,w=1}
    self.entity.sprite.texture = graphics.texture.get("tile0")
end

function ComponentPlacer:onMouseJustDown()
    self.entity.sprite.color = {x=1,y=0,z=0,w=1}

    self.game:moveTiles(self.col, self.row, self.sens)
end