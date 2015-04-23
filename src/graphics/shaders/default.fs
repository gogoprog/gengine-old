GL_GLSL(

varying highp vec2 v_texCoords;
uniform sampler2D tex0;
uniform highp vec4 color;

void main()
{
    gl_FragColor = texture2D(tex0, v_texCoords) * color;
}

);