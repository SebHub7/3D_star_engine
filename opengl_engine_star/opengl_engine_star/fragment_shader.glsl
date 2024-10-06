#version 330 core
out vec4 FragColor;
in vec3 n;
const vec3 light = vec3(0, 0, 1);

void main()
{
    float cos = dot(n, light);
    FragColor = vec4(vec3(1) * cos, 1);
} 