#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 text_coord;
layout (location = 2) in vec3 normal;

uniform mat4 vp;
out vec3 n;

void main()
{
    n = normal;
    gl_Position = vp * vec4(pos, 1.0);
}