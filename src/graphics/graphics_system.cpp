#include "graphics_system.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"
#include "graphics_shader.h"
#include "graphics_vertex_buffer.h"
#include "graphics_texture_manager.h"
#include "graphics_animation_manager.h"
#include "graphics_atlas_manager.h"
#include "graphics_spriter_manager.h"
#include "graphics_font_manager.h"
#include "graphics_world.h"
#include "vector4.h"
#include "application.h"
#include <math.h>

namespace gengine
{
namespace graphics
{

void System::init()
{
    geDebugLog("graphics::System::init()");

    renderer.init();

    TextureManager::getInstance().init("texture");
    TextureManager::getInstance().addSupportedExtension(".png");
    AtlasManager::getInstance().init("atlas");
    AnimationManager::getInstance().init("animation");
    SpriterManager::getInstance().init("Spriter animation");
    SpriterManager::getInstance().addSupportedExtension(".scon");
    FontManager::getInstance().init("font");

    defaultCamera.setExtent(application::getExtent());

    setClearColor(Vector4(0.2f,0.2f,0.2f,1.0f));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    createWorlds(1);

    whiteTexture.init();
    whiteTexture.setWhite();
}

void System::finalize()
{
    geDebugLog("graphics::System::finalize()");

    for(World * world : worldTable)
    {
        world->finalize();
    }

    FontManager::getInstance().finalize();
    SpriterManager::getInstance().finalize();
    AnimationManager::getInstance().finalize();
    AtlasManager::getInstance().finalize();
    TextureManager::getInstance().finalize();

    renderer.finalize();
}

void System::update()
{
    for(World * world : worldTable)
    {
        world->update();
    }
}

void System::render()
{
    for(World * world : worldTable)
    {
        renderer.render(* world);
    }
}

void System::setClearColor(const Vector4 & c)
{
    glClearColor(c.x, c.y ,c.z, c.w);
}

void System::createWorlds(const uint count)
{
    int new_count = count - worldTable.getSize();

    for(int i=0; i<new_count; ++i)
    {
        World * world = new World();
        world->init();
        worldTable.add(world);
    }
}

World & System::getWorld(const uint index)
{
    return * worldTable[index];
}

}
}
