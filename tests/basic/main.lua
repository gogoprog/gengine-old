print("tests/basic")

ComponentCustom = {}

function ComponentCustom:init()
    self.entity.sprite.color = {x=0.3,y=0.3,z=0.3,w=1}
end

function ComponentCustom:insert()
end

function ComponentCustom:update(dt)
end

function ComponentCustom:remove()
end

function ComponentCustom:onMouseEnter()
    self.entity.sprite.color = {x=1,y=1,z=1,w=1}
end

function ComponentCustom:onMouseExit()
    self.entity.sprite.color = {x=0.3,y=0.3,z=0.3,w=1}
end

function ComponentCustom:onMouseJustDown()
    self.entity.sprite.color = {x=1,y=0,z=0,w=1}
end

function init()
    application.setName("gengine-tests:basic")
    application.setExtent(640,480)
end

local e, cameraEntity

function start()
    print("tests/basic start")

    entity.registerCustomComponent(ComponentCustom)

    graphics.setClearColor(1,1,0.1,1)

    graphics.texture.create("bird.png")
    graphics.texture.create("logo.png")

    e = entity.create()
    e.name = "Yeah"

    e:addComponent(ComponentSprite(), { texture = graphics.texture.get("logo"), extent = { x=256, y=128 } }, "sprite")
    e:addComponent(ComponentMouseable(), { extent = { x=256, y=128} })
    e:addComponent(ComponentCustom(), {}, "custom")

    e:insert()

    cameraEntity = entity.create()
    cameraEntity:addComponent(ComponentCamera(), { extent = { x=640, y=480} }, "camera")
    cameraEntity:insert()
end

local total = 0
local layer = 0
local my_entities = {}

function update(dt)
    total = total + dt

    graphics.setClearColor(1,1,math.sin(total),1)

    if input.mouse:isJustDown(1) then
        local x,y = input.mouse:getPosition()
        local wx, wy = cameraEntity.camera:getWorldPosition(x,y)

        local et
        et = entity.create()
        et:addComponent(ComponentSprite(),
            {
                texture = graphics.texture.get("bird"),
                layer = layer,
                extent = { x=64, y=64 },
                color = { x=0.5, y=0.9, z=0.6, w=1.0 }
            })

        et:insert()
        et.position.x = wx
        et.position.y = wy

        layer = layer + 1

        table.insert(my_entities, et)
    end

    for k,v in ipairs(my_entities) do
        v.rotation = v.rotation + dt
    end
end

function stop()
    print("tests/basic end")
end
