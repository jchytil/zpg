#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec3 vColor;
out vec3 vNormal;

void main()
{
    if (gl_VertexID > 36443)
    {
        vColor = vec3(0.13, 0.55, 0.13);
    }
    else
    {
        vColor = vec3(0.4, 0.25, 0.1);
    }

    vNormal = normal;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}