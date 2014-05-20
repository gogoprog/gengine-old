function init()
    application.setName("[gengine-tests] 02-mouseable")
    application.setExtent(640,480)
end

local logoEntity

function start()
    graphics.setClearColor(0,0.1,0.1,1)

    graphics.texture.create("logo.png")

    logoEntity = entity.create()

    logoEntity:addComponent(
        ComponentSprite(),
        {
            texture = graphics.texture.get("logo"),
            extent = { x=256, y=128 },
            layer = 0
        },
        "sprite"
        )

    logoEntity:addComponent(
        ComponentMouseable(),
        {
            extent = { x=256, y=128 }
        },
        "mouseable"
        )

    logoEntity.onMouseEnter = function(e)
        local extent = { x=300, y=140 }
        e.sprite.extent = extent
        e.mouseable.extent = extent
        e.sprite.color = {x=1,y=0,z=0,w=1}
    end

    logoEntity.onMouseExit = function(e)
        local extent = { x=256, y=128 }
        e.sprite.extent = extent
        e.mouseable.extent = extent
        e.sprite.color = {x=1,y=1,z=1,w=1}
    end

    logoEntity.onMouseJustDown = function(e)
        e.position.y = e.position.y - 16
    end

    logoEntity.position.y = 128
    logoEntity:insert()
end

function update(dt)
end