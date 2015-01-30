GL_GLSL(

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
    gl_Position = vec4(res, 1.0);
}

);