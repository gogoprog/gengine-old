GL_GLSL(

varying highp vec2 v_texCoords;
varying highp vec4 v_color;

uniform sampler2D tex0;
uniform highp vec4 colorUniform;

void main()
{
    gl_FragColor = texture2D(tex0, v_texCoords) * colorUniform * v_color;
}

);
