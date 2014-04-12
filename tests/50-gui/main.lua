function init()
    application.setName("[gengine-tests] 50-gui")
    application.setExtent(1024,800)
end

local logoEntity

function start()
    graphics.setClearColor(0,0.1,0.1,1)

    graphics.texture.load("logo.png")

    logoEntity = entity.create()

    logoEntity:addComponent(
        ComponentSprite(),
        {
            texture = graphics.texture.get("logo"),
            extent = { x=256, y=128 },
            layer = 0
        }
        )

    logoEntity:insert()
end

local total = 0
function update(dt)
    total = total + dt
    logoEntity.rotation = total
end
