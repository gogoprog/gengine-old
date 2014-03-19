print("tests/basic")

function init()
    application.setName("gengine-tests:basic")
    application.setExtent(320,200)
end

local e

function start()
    print("tests/basic start")
    graphics.setClearColor(1,1,0.1,1)

    local te = entity.create()

    print(te.name)
    print(te.position.x)
    print(te.position.y)

    e = entity.create()
    e.name = "Yeah"
end

local total = 0

function update(dt)
    total = total + dt
    print(e.rotation)
    graphics.setClearColor(1,1,math.sin(total),1)

    for i=1,3 do
        if input.mouse:isJustDown(i) then
            local x,y = input.mouse:getPosition()
            print("Mouse button " .. i .. " is just down @(" .. x .. ", " .. y .. ")")
        end
    end
end

function stop()
    print("tests/basic end")
end
