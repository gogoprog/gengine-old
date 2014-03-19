print("tests/basic")

function init()
    print("tests/basic init")
    application.setExtent(320,200)
end

function start()
    print("tests/basic start")
    graphics.setClearColor(1,1,0.1,1)
end

local total = 0

function update(dt)
    total = total + dt

    graphics.setClearColor(1,1,math.sin(total),1)


    if input.mouse:isJustDown(1) then
        local x,y = input.mouse:getPosition()
        print("Mouse button 1 is down : " .. x .. ", " ..y)
    end

    if input.mouse:isJustDown(3) then
        local x,y = input.mouse:getPosition()
        print("Mouse button 3 is down : " .. x .. ", " ..y)
    end
end

function stop()
    print("tests/basic end")
end
