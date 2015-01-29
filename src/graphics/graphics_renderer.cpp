#include "graphics_renderer.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "graphics_sprite.h"
#include "graphics_sprite_batch.h"
#include "graphics_atlas.h"

#define INDEX_BUFFER_SIZE 102400

namespace gengine
{
namespace graphics
{

const char vertex_shader_source[] = GL_GLSL(
    attribute vec2 position;
    attribute vec2 texCoords;
    varying highp vec2 v_texCoords;
    uniform highp mat3 projectionMatrix;
    uniform highp mat3 transformMatrix;
    uniform highp vec2 uvScale;
    uniform highp vec2 uvOffset;

    void main()
    {
        vec3 res = transformMatrix * vec3(position, 1.0) * projectionMatrix;
        v_texCoords.x = texCoords.x * uvScale.x + uvOffset.x;
        v_texCoords.y = texCoords.y * uvScale.y + uvOffset.y;
        gl_Position = vec4(res,1.0);
    }
);

const char fragment_shader_source[] = GL_GLSL(
    varying highp vec2 v_texCoords;
    uniform sampler2D tex0;
    uniform highp vec4 color;

    void main()
    {
        gl_FragColor = texture2D(tex0, v_texCoords) * color;
    }
);

const char particle_vertex_shader_source[] = GL_GLSL(
    attribute vec2 position;
    attribute vec4 color;
    attribute uint index;
    attribute float rotation;
    varying highp vec2 v_texCoords;
    uniform highp mat3 projectionMatrix;
    uniform highp mat3 transformMatrix;
    uniform highp vec2 halfParticleSize;

    void main()
    {
        vec3 finalPosition;

        if(index == 0)
        {
            finalPosition.x = position.x - halfParticleSize.x;
            finalPosition.y = position.y - halfParticleSize.y;
        }
        else if(index == 1)
        {
            finalPosition.x = position.x + halfParticleSize.x;
            finalPosition.y = position.y - halfParticleSize.y;
        }
        else if(index == 2)
        {
            finalPosition.x = position.x + halfParticleSize.x;
            finalPosition.y = position.y + halfParticleSize.y;
        }
        else if(index == 3)
        {
            finalPosition.x = position.x - halfParticleSize.x;
            finalPosition.y = position.y + halfParticleSize.y;
        }

        vec3 res = transformMatrix * vec3(finalPosition, 1.0) * projectionMatrix;
        v_texCoords.x = texCoords.x * uvScale.x + uvOffset.x;
        v_texCoords.y = texCoords.y * uvScale.y + uvOffset.y;
        gl_Position = vec4(res,1.0);
    }
);

const char particle_fragment_shader_source[] = GL_GLSL(
    varying highp vec2 v_texCoords;
    uniform sampler2D tex0;
    uniform highp vec4 color;

    void main()
    {
        gl_FragColor = texture2D(tex0, v_texCoords) * color;
    }
);

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
    defaultVertexShader.compile(vertex_shader_source);

    defaultFragmentShader.init(GL_FRAGMENT_SHADER);
    defaultFragmentShader.compile(fragment_shader_source);

    defaultProgram.init();
    defaultProgram.attachShader(defaultVertexShader);
    defaultProgram.attachShader(defaultFragmentShader);
    defaultProgram.link();

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

    vertices[1].position.x = 0.5f;
    vertices[1].position.y = 0.5f;
    vertices[1].texCoords.u = 1.0f;
    vertices[1].texCoords.v = 0.0f;

    vertices[2].position.x = 0.5f;
    vertices[2].position.y = -0.5f;
    vertices[2].texCoords.u = 1.0f;
    vertices[2].texCoords.v = 1.0f;

    vertices[3].position.x = -0.5f;
    vertices[3].position.y = -0.5f;
    vertices[3].texCoords.u = 0.0f;
    vertices[3].texCoords.v = 1.0f;

    vertexBufferQuad.unMap();

    indexBufferQuad.init();
    indexBufferQuad.setData(indices, INDEX_BUFFER_SIZE);

    projectionMatrixUniform.init(defaultProgram, "projectionMatrix");
    transformMatrixUniform.init(defaultProgram, "transformMatrix");
    samplerUniform.init(defaultProgram, "tex0");
    colorUniform.init(defaultProgram, "color");
    uvScaleUniform.init(defaultProgram, "uvScale");
    uvOffsetUniform.init(defaultProgram, "uvOffset");
}

void Renderer::finalize()
{
    defaultProgram.finalize();
    defaultFragmentShader.finalize();
    defaultVertexShader.finalize();
    vertexBufferQuad.finalize();
    indexBufferQuad.finalize();
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

                if(batch.atlas && batch.atlas->hasTexture())
                {
                    batch.vertexBuffer.apply();

                    transform_matrix.initIdentity();
                    transform_matrix.setTranslation(batch.position);

                    transformMatrixUniform.apply(transform_matrix);

                    colorUniform.apply(batch.color);

                    samplerUniform.apply(batch.atlas->getTexture());

                    uvScaleUniform.apply(Vector2::one);
                    uvOffsetUniform.apply(Vector2::zero);

                    indexBufferQuad.draw(6 * batch.getItemCount());
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
            {
                if(currentProgram != & defaultProgram)
                {
                    defaultProgram.use();
                    currentProgram = & defaultProgram;
                }

                projectionMatrixUniform.apply(world.getCurrentCamera().getProjectionMatrix());
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
