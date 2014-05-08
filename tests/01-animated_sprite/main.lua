function init()
    application.setName("[gengine-tests] 01-animated_sprite")
    application.setExtent(320,200)
end

local logoEntity

function start()
    graphics.setClearColor(0,0.1,0.1,1)

    local texture = graphics.texture.create("man.png")

    local atlas = graphics.atlas.create("test", texture, 12, 8)

    local animation = graphics.animation.create("testa",
        {
            atlas = atlas,
            frames = { 0, 1, 2, 1 },
            framerate = 5
        }
        )

    logoEntity = entity.create()

    logoEntity:addComponent(
        ComponentAnimatedSprite(),
        {
            animation = animation,
            extent = { x=128, y=128 },
            layer = 0
        }
        )

    logoEntity:insert()
end

function update(dt)
end
