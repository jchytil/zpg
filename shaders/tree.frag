#version 330 core
in vec3 vColor;
in vec3 vNormal;
out vec4 FragColor;

void main()
{
    float shade = 0.3 + 0.7 * abs(vNormal.y);
    FragColor = vec4(shade * vColor, 1.0);
}