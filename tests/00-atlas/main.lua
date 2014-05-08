function init()
    application.setName("[gengine-tests] 01-sprite")
    application.setExtent(320,200)
end

local logoEntity

function start()
    graphics.setClearColor(0,0.1,0.1,1)

    local texture = graphics.texture.create("logo.png")

    graphics.atlas.create("test", texture, 5, 1)

    logoEntity = entity.create()

    logoEntity:addComponent(
        ComponentSprite(),
        {
            atlas = graphics.atlas.get("test"),
            atlasItem = 4,
            extent = { x=256, y=128 },
            layer = 0
        }
        )

    logoEntity:insert()
end

function update(dt)
end
