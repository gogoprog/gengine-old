GL_GLSL(

attribute vec2 position;
attribute vec4 color;
attribute float rotation;
attribute float index;
attribute float life;

varying highp vec2 v_texCoords;
varying highp vec4 v_color;

uniform highp mat3 projectionMatrix;
uniform highp mat3 transformMatrix;

uniform highp vec2 extentTable[8];
uniform highp int extentCount;

uniform highp vec4 colorTable[8];
uniform highp int colorCount;

vec2 getExtent(float factor)
{
    if(extentCount==1)
    {
        return extentTable[0];
    }

    int lower;
    int upper;
    float f = factor * float(extentCount - 1);

    lower = int(floor(f));
    upper = int(ceil(f));

    if(lower==upper)
    {
        return extentTable[lower];
    }

    f = f - float(lower);

    vec2 result;

    result = extentTable[lower] + (extentTable[upper] - extentTable[lower]) * f;

    return result;
}

void main()
{
    vec2 finalPosition;
    int i = int(index);

    vec2 extent = getExtent(life);

    if(i == 0)
    {
        finalPosition.x = position.x - extent.x * 0.5;
        finalPosition.y = position.y + extent.y * 0.5;
        v_texCoords = vec2(0, 0);
    }
    else if(i == 1)
    {
        finalPosition.x = position.x + extent.x * 0.5;
        finalPosition.y = position.y + extent.y * 0.5;
        v_texCoords = vec2(1, 0);
    }
    else if(i == 2)
    {
        finalPosition.x = position.x + extent.x * 0.5;
        finalPosition.y = position.y - extent.y * 0.5;
        v_texCoords = vec2(1, 1);
    }
    else if(i == 3)
    {
        finalPosition.x = position.x - extent.x * 0.5;
        finalPosition.y = position.y - extent.y * 0.5;
        v_texCoords = vec2(0, 1);
    }

    v_color = color;
    v_color.a = 1.0 - life;

    vec3 res = transformMatrix * vec3(finalPosition, 1.0) * projectionMatrix;
    gl_Position = vec4(res, 1.0);
}

);