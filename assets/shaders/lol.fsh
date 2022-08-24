#version 330 core

in vec3 vs_color;
in vec2 vs_uv;

out vec4 color;

uniform sampler2D texture1;

void main()
{
    color = texture(texture1, vs_uv);
}
