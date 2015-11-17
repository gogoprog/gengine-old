#include "graphics_renderer.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "graphics_sprite.h"
#include "graphics_sprite_batch.h"
#include "graphics_sprite_group.h"
#include "graphics_particle_system.h"
#include "graphics_atlas.h"
#include "graphics_text.h"
#include "graphics_mesh.h"
#include "core.h"

#define INDEX_BUFFER_SIZE 102400

namespace gengine
{
namespace graphics
{

const char default_vs_source[] =
    #include "shaders/default.vs"

const char default_fs_source[] =
    #include "shaders/default.fs"

const char particle_vs_source[] =
    #include "shaders/particle.vs"

const char particle_fs_source[] =
    #include "shaders/particle.fs"

Renderer::Renderer()
    :
    currentType(Type::NONE)
{
}

void Renderer::init()
{
    Vertex * vertices;
    ushort indices[INDEX_BUFFER_SIZE];

    defaultVertexShader.init(GL_VERTEX_SHADER);
    defaultVertexShader.compile(default_vs_source, "default.vs");

    defaultFragmentShader.init(GL_FRAGMENT_SHADER);
    defaultFragmentShader.compile(default_fs_source, "default.fs");

    defaultProgram.init();
    defaultProgram.attachShader(defaultVertexShader);
    defaultProgram.attachShader(defaultFragmentShader);
    defaultProgram.link();

    particleVertexShader.init(GL_VERTEX_SHADER);
    particleVertexShader.compile(particle_vs_source, "particle.vs");

    particleFragmentShader.init(GL_FRAGMENT_SHADER);
    particleFragmentShader.compile(particle_fs_source, "particle.fs");

    particleProgram.init();
    particleProgram.attachShader(particleVertexShader);
    particleProgram.attachShader(particleFragmentShader);
    particleProgram.link();

    for(uint i=0; i<INDEX_BUFFER_SIZE/6; ++i)
    {
        indices[i*6 + 0] = i*4 + 0;
        indices[i*6 + 1] = i*4 + 1;
        indices[i*6 + 2] = i*4 + 2;

        indices[i*6 + 3] = i*4 + 2;
        indices[i*6 + 4] = i*4 + 3;
        indices[i*6 + 5] = i*4 + 0;
    }

    vertexBufferQuad.init(4, false);

    vertices = vertexBufferQuad.map();

    vertices[0].position.x = -0.5f;
    vertices[0].position.y = 0.5f;
    vertices[0].texCoords.u = 0.0f;
    vertices[0].texCoords.v = 0.0f;
    vertices[0].color = Vector4::one;

    vertices[1].position.x = 0.5f;
    vertices[1].position.y = 0.5f;
    vertices[1].texCoords.u = 1.0f;
    vertices[1].texCoords.v = 0.0f;
    vertices[1].color = Vector4::one;

    vertices[2].position.x = 0.5f;
    vertices[2].position.y = -0.5f;
    vertices[2].texCoords.u = 1.0f;
    vertices[2].texCoords.v = 1.0f;
    vertices[2].color = Vector4::one;

    vertices[3].position.x = -0.5f;
    vertices[3].position.y = -0.5f;
    vertices[3].texCoords.u = 0.0f;
    vertices[3].texCoords.v = 1.0f;
    vertices[3].color = Vector4::one;

    vertexBufferQuad.unMap();

    indexBufferQuad.init(INDEX_BUFFER_SIZE, false);
    indexBufferQuad.setData(indices, INDEX_BUFFER_SIZE);

    projectionMatrixUniform.init(defaultProgram, "projectionMatrix");
    transformMatrixUniform.init(defaultProgram, "transformMatrix");
    samplerUniform.init(defaultProgram, "tex0");
    colorUniform.init(defaultProgram, "colorUniform");
    uvScaleUniform.init(defaultProgram, "uvScale");
    uvOffsetUniform.init(defaultProgram, "uvOffset");

    particleProjectionMatrixUniform.init(particleProgram, "projectionMatrix");
    particleTransformMatrixUniform.init(particleProgram, "transformMatrix");
    particleSamplerUniform.init(particleProgram, "tex0");
    particleColorUniform.init(particleProgram, "color");

    particleColorUniforms.init(particleProgram, "color");
    particleScaleUniforms.init(particleProgram, "scale");
}

void Renderer::finalize()
{
    defaultProgram.finalize();
    defaultFragmentShader.finalize();
    defaultVertexShader.finalize();
    vertexBufferQuad.finalize();
    indexBufferQuad.finalize();

    particleProgram.finalize();
    particleFragmentShader.finalize();
    particleVertexShader.finalize();
}

void Renderer::render(const World & world)
{
    Matrix3 transform_matrix;

    for(Object * object : world.objectTable)
    {
        Type type = object->getRenderType();
        enable(type, world);

        switch(type)
        {
            case Type::SPRITE:
            {
                Sprite & sprite = * dynamic_cast<Sprite *>(object);

                if(sprite.texture)
                {
                    transform_matrix.initIdentity();
                    transform_matrix.setTranslation(sprite.position);
                    transform_matrix.setRotation(sprite.rotation);
                    transform_matrix.preScale(sprite.extent);

                    transformMatrixUniform.apply(transform_matrix);

                    colorUniform.apply(sprite.color);

                    samplerUniform.apply(* sprite.texture);

                    uvScaleUniform.apply(sprite.uvScale);
                    uvOffsetUniform.apply(sprite.uvOffset);

                    indexBufferQuad.draw(6);
                }
            }
            break;

            case Type::SPRITE_BATCH:
            {
                SpriteBatch & batch = * dynamic_cast<SpriteBatch *>(object);

                if(batch.texture)
                {
                    batch.vertexBuffer.apply();

                    transform_matrix.initIdentity();
                    transform_matrix.setTranslation(batch.position);
                    transform_matrix.preScale(batch.scale);

                    transformMatrixUniform.apply(transform_matrix);

                    colorUniform.apply(batch.color);

                    samplerUniform.apply(* batch.texture);

                    uvScaleUniform.apply(Vector2::one);
                    uvOffsetUniform.apply(Vector2::zero);

                    indexBufferQuad.draw((batch.getVertexCount() / 4) * 6);
                }
            }
            break;

            case Type::MESH:
            {
                auto & mesh = * dynamic_cast<Mesh<Vertex> *>(object);

                if(mesh.texture)
                {
                    mesh.vertexBuffer.apply();

                    transform_matrix.initIdentity();
                    transform_matrix.setTranslation(mesh.position);
                    transform_matrix.preScale(mesh.scale);

                    transformMatrixUniform.apply(transform_matrix);

                    colorUniform.apply(mesh.color);

                    samplerUniform.apply(* mesh.texture);

                    uvScaleUniform.apply(Vector2::one);
                    uvOffsetUniform.apply(Vector2::zero);

                    mesh.indexBuffer.draw(mesh.indexCount);
                }
            }
            break;

            case Type::SPRITE_GROUP:
            {
                SpriteGroup & sprite_group = * dynamic_cast<SpriteGroup *>(object);

                for(uint i=0; i<sprite_group.activeCount; ++i)
                {
                    auto & sprite = * sprite_group.sprites[i];

                    if(sprite.texture)
                    {
                        transform_matrix.initIdentity();
                        transform_matrix.setTranslation(sprite_group.position + math::Vector2::getRotated(sprite.position, sprite_group.rotation));
                        transform_matrix.setRotation(sprite.rotation + sprite_group.rotation);
                        transform_matrix.preScale(sprite.extent);

                        transformMatrixUniform.apply(transform_matrix);

                        colorUniform.apply(sprite.color * sprite_group.color);

                        samplerUniform.apply(* sprite.texture);

                        uvScaleUniform.apply(sprite.uvScale);
                        uvOffsetUniform.apply(sprite.uvOffset);

                        indexBufferQuad.draw(6);
                    }
                }
            }
            break;

            case Type::PARTICLE_SYSTEM:
            {
                ParticleSystem & particle_system = * dynamic_cast<ParticleSystem *>(object);

                if(particle_system.particleCount)
                {
                    particle_system.vertexBuffer.apply();

                    transform_matrix.initIdentity();

                    if(particle_system.keepsLocal())
                    {
                        transform_matrix.setTranslation(particle_system.position);
                    }

                    particleTransformMatrixUniform.apply(transform_matrix);
                    particleColorUniform.apply(particle_system.color);
                    particleSamplerUniform.apply(* particle_system.texture);

                    particleColorUniforms.apply(particle_system.colorTable);
                    particleScaleUniforms.apply(particle_system.scaleTable);

                    indexBufferQuad.draw(6 * particle_system.particleCount);
                }
            }
            break;

            case Type::TEXT:
            {
                Text & text = * dynamic_cast<Text *>(object);

                if(text.surface)
                {
                    transform_matrix.initIdentity();
                    transform_matrix.setTranslation(text.position);
                    transform_matrix.setRotation(text.rotation);
                    transform_matrix.preScale(text.extent);

                    transformMatrixUniform.apply(transform_matrix);

                    colorUniform.apply(text.color);
                    samplerUniform.apply(text.texture);

                    uvScaleUniform.apply(Vector2::one);
                    uvOffsetUniform.apply(Vector2::zero);

                    indexBufferQuad.draw(6);
                }
            }
            break;

            default:
            break;
        }
    }

    glUseProgram(0);
    currentType = Type::NONE;
    currentProgram = nullptr;
}

void Renderer::enable(const Type type, const World & world)
{
    if(currentType != type)
    {
        switch(type)
        {
            case Type::SPRITE:
            case Type::SPRITE_GROUP:
            case Type::TEXT:
            {
                if(currentProgram != & defaultProgram)
                {
                    defaultProgram.use();
                    currentProgram = & defaultProgram;
                }

                projectionMatrixUniform.apply(world.getCurrentCamera().getProjectionMatrix());
                vertexBufferQuad.apply();
            }
            break;

            case Type::SPRITE_BATCH:
            case Type::MESH:
            {
                if(currentProgram != & defaultProgram)
                {
                    defaultProgram.use();
                    currentProgram = & defaultProgram;
                }

                projectionMatrixUniform.apply(world.getCurrentCamera().getProjectionMatrix());
            }
            break;

            case Type::PARTICLE_SYSTEM:
            {
                if(currentProgram != & particleProgram)
                {
                    particleProgram.use();
                    currentProgram = & particleProgram;
                }

                particleProjectionMatrixUniform.apply(world.getCurrentCamera().getProjectionMatrix());
            }
            break;

            default:
            break;
        };

        currentType = type;
    }
}

}
}
