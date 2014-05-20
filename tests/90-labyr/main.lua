dofile("game.lua")

function init()
    application.setName("[gengine-tests] 90-labyr")
    application.setExtent(800,600)
end

local logoEntity

local game = Game()

function start()
    graphics.setClearColor(0.6,0.6,1,1)

    game:load()
end

function update(dt)
    game:update(dt)
end
