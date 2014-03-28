print("tests/basic")

function init()
    application.setName("gengine-tests:basic")
    --application.setExtent(320,200)
end

local e

function start()
    print("tests/basic start")
    graphics.setClearColor(1,1,0.1,1)

    e = entity.create()
    e.name = "Yeah"

    e:addComponent(ComponentSprite(), { texture = 0, extent = { x=256, y=256 } })

    e:insert()
end

local total = 0
local layer = 0
local my_entities = {}
function update(dt)
    total = total + dt

    graphics.setClearColor(1,1,math.sin(total),1)

    if input.mouse:isJustDown(1) then
        local x,y = input.mouse:getPosition()
        local wx, wy = graphics.getWorldPosition(x,y)

        local et
        et = entity.create()
        et:addComponent(ComponentSprite(),
            {
                texture = 0,
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

    if input.mouse:isJustDown(2) then
        e.components.sprite.layer = 100
        e.components.sprite.extent = { x=138,y=128}
    end

    for k,v in ipairs(my_entities) do
        v.rotation = v.rotation + dt
    end

    e.rotation = total;
end

function stop()
    print("tests/basic end")
end
