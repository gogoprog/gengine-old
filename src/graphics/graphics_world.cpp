#include "graphics_world.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "graphics_sprite.h"
#include <algorithm>

namespace gengine
{
namespace graphics
{

World::World()
{
}

void World::init()
{
    cameraStack.push(&System::getInstance().getDefaultCamera());

    Program & program = System::getInstance().getDefaultProgram();

    projectionMatrixUniform.init(program, "projectionMatrix");
    transformMatrixUniform.init(program, "transformMatrix");
    samplerUniform.init(program, "tex0");
    colorUniform.init(program, "color");
}

void World::finalize()
{

}

void World::update()
{
    cameraStack.getTop()->update();

    std::sort(spriteTable.begin(), spriteTable.end(), compare);
}

void World::render()
{
    System & system = System::getInstance();
    Matrix3 transform_matrix;

    system.getDefaultProgram().use();
    system.getVertexBufferQuad().apply();

    projectionMatrixUniform.apply(cameraStack.getTop()->getProjectionMatrix());

    for(Sprite * _sprite : spriteTable)
    {
        Sprite & sprite = * _sprite;

        transform_matrix.initIdentity();
        transform_matrix.setTranslation(sprite.position);
        transform_matrix.setRotation(sprite.rotation);
        transform_matrix.preScale(sprite.extent);

        transformMatrixUniform.apply(transform_matrix);

        colorUniform.apply(sprite.color);

        samplerUniform.apply(* sprite.texture);

        system.getIndexBufferQuad().draw();
    }
}

void World::addSprite(Sprite & sprite)
{
    spriteTable.add(&sprite);
}

bool World::compare(Sprite *a, Sprite *b)
{
    return a->layer > b->layer || ( a->layer == b->layer && a > b);
}

}
}
