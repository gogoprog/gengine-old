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

    for i = 1,3 do
        if input.mouse:isJustDown(i) then
            local x,y = input.mouse:getPosition()
            print("Mouse button " .. i .. " is just down @(" .. x .. ", " .. y .. ")")

            local wx, wy = graphics.getWorldPosition(x,y)

            local et
            et = entity.create()
            et:addComponent(ComponentSprite(),
                {
                    texture = 0,
                    layer = layer,
                    color = { x=0.5, y=0.9, z=0.6, w=1.0 }
                })

            et:insert()
            et.position.x = wx
            et.position.y = wy

            et.components.sprite.blabla = "truc"

            layer = layer - 1

            table.insert(my_entities, et)
        end
    end

    for k,v in ipairs(my_entities) do
        v.rotation = v.rotation + dt
    end

    e.rotation = total;
end

function stop()
    print("tests/basic end")
end
