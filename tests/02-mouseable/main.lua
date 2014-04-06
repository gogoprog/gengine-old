function init()
    application.setName("[gengine-tests] 02-mouseable")
    application.setExtent(640,480)
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

    logoEntity:addComponent(
        ComponentMouseable(),
        {
            extent = { x=256, y=128 }
        }
        )

    logoEntity.onMouseEnter = function(o)
        o.sprite.color = {x=1,y=0,z=0,w=1}
    end

    logoEntity.onMouseExit = function(o)
        o.sprite.color = {x=1,y=1,z=1,w=1}
    end

    logoEntity.onMouseJustDown = function(o)
        o.position.y = o.position.y - 16
    end

    logoEntity.position.y = 128
    logoEntity:insert()
end

function update(dt)
end