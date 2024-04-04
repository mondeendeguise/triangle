#version 330 core

out vec4 f_color;

in vec2 uv;
in vec4 color;

void main()
{
    f_color = vec4(0.5f, 0.2f, 0.2f, 1.0f);
}
