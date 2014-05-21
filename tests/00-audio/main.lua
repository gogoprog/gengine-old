function init()
    application.setName("[gengine-tests] 00-audio")
    application.setExtent(320,200)
end

function start()
    graphics.setClearColor(0.5,0.1,0.1,1)

    audio.playMusic("test03.mp3")
end

function update(dt)
end
