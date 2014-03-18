print("tests/basic")

function init()
    print("tests/basic init")
    setExtent(800,600)
end

function start()
    print("tests/basic start")
    graphics.setClearColor(1,1,0.1,1)
end

function update(dt)
    if input.mouse:isDown(1) then
        print("Mouse button 1 is down")
    end

    if input.mouse:isDown(3) then
        print("Mouse button 3 is down")
    end
end

function stop()
    print("tests/basic end")
end
