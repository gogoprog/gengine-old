-- Custom components

ComponentCustom = {}

function ComponentCustom:init()
    self.total = 0
end

function ComponentCustom:insert()
end

function ComponentCustom:update(dt)
    local e = self.entity
    self.total = self.total + dt * self.speed
    e.position.x = math.sin(self.total) * self.distance
    e.rotation = math.sin(self.total) * self.angle
end

function ComponentCustom:remove()
end

-- App

function init()
    application.setName("[gengine-tests] 10-custom_component")
    application.setExtent(320,600)
end


function start()
    graphics.setClearColor(0,0.1,0.1,1)

    graphics.texture.create("logo.png")

    entity.registerCustomComponent(ComponentCustom)

    for i=0,8 do
        local logoEntity = entity.create()

        logoEntity:addComponent(
            ComponentSprite(),
            {
                texture = graphics.texture.get("logo"),
                extent = { x=256, y=128 },
                layer = 0
            }
            )

        logoEntity:addComponent(
            ComponentCustom(),
            {
                distance = math.random(10,100),
                angle = math.random(0.1,0.3),
                speed = math.random(5,10),
            }
            )

        logoEntity:insert()

        logoEntity.position.y = -256 + i * 64
    end
end

function update(dt)

end

