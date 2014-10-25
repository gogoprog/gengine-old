#include "graphics_renderer.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "graphics_sprite.h"

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
        vec3 res = transformMatrix * vec3(position,1.0 ) * projectionMatrix;
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

Renderer::Renderer()
    :
    currentType(Type::NONE)
{
}

void Renderer::init()
{
    Vertex vertices[4];
    ushort indices[6];

    defaultVertexShader.init(GL_VERTEX_SHADER);
    defaultVertexShader.compile(vertex_shader_source);

    defaultFragmentShader.init(GL_FRAGMENT_SHADER);
    defaultFragmentShader.compile(fragment_shader_source);

    defaultProgram.init();
    defaultProgram.attachShader(defaultVertexShader);
    defaultProgram.attachShader(defaultFragmentShader);
    defaultProgram.link();

    vertices[0].x = -0.5f;
    vertices[0].y = 0.5f;
    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;

    vertices[1].x = 0.5f;
    vertices[1].y = 0.5f;
    vertices[1].u = 1.0f;
    vertices[1].v = 0.0f;

    vertices[2].x = 0.5f;
    vertices[2].y = -0.5f;
    vertices[2].u = 1.0f;
    vertices[2].v = 1.0f;

    vertices[3].x = -0.5f;
    vertices[3].y = -0.5f;
    vertices[3].u = 0.0f;
    vertices[3].v = 1.0f;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    vertexBufferQuad.init();
    vertexBufferQuad.setData(vertices, 4);

    indexBufferQuad.init();
    indexBufferQuad.setData(indices, 6);

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

    for(Sprite * _sprite : world.spriteTable)
    {
        Sprite & sprite = * _sprite;

        enable(sprite.renderType, world);

        transform_matrix.initIdentity();
        transform_matrix.setTranslation(sprite.position);
        transform_matrix.setRotation(sprite.rotation);
        transform_matrix.preScale(sprite.extent);

        transformMatrixUniform.apply(transform_matrix);

        colorUniform.apply(sprite.color);

        samplerUniform.apply(* sprite.texture);

        uvScaleUniform.apply(sprite.uvScale);
        uvOffsetUniform.apply(sprite.uvOffset);

        indexBufferQuad.draw();
    }

    glUseProgram(0);
    currentType = Type::NONE;
}

void Renderer::enable(const Type type, const World & world)
{
    if(currentType != type)
    {
        switch(type)
        {
            case Type::SPRITE:
            {
                defaultProgram.use();
                vertexBufferQuad.apply();
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
