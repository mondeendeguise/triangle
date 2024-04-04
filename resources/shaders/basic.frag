#version 330 core
out vec4 f_color;

in vec2 uv;
in vec4 color;

void main()
{
    f_color = color;
}
