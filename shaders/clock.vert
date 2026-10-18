#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform float hourAngle;
uniform float minuteAngle;
uniform float secondAngle;

out vec3 vColor;

vec3 RotateZ(vec3 p, float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return vec3(p.x * c - p.y * s, p.x * s + p.y * c, p.z);
}

void main()
{
    vec3 p = position;
    vec3 finalColor = color;

    if (color == vec3(1.0, 0.0, 0.0))
    {
        p = RotateZ(p, -secondAngle);
    }
    else if (color == vec3(0.0, 1.0, 0.0))
    {
        p = RotateZ(p, -minuteAngle);
        finalColor = vec3(0.0, 0.0, 0.0);
    }
    else if (color == vec3(0.0, 0.0, 1.0))
    {
        p = RotateZ(p, -hourAngle);
        finalColor = vec3(0.0, 0.0, 0.0);
    }
    else if (color == vec3(1.0, 1.0, 0.0))
    {
        finalColor = vec3(5.0 / 255.0, 195.0 / 255.0, 222.0 / 255.0);
    }
    else if (color == vec3(0.0, 0.0, 0.0))
    {
        finalColor = vec3(0.55, 0.55, 0.55);
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(p, 1.0);
    vColor = finalColor;
}