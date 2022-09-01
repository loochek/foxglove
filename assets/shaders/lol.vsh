#version 330 core

layout (location = 0) in vec3 position;
// layout (location = 1) in vec3 color;
layout (location = 1) in vec2 uv;

// out vec3 vs_color;
out vec2 vs_uv;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
//     vs_color = color;
    vs_uv = uv;
}

