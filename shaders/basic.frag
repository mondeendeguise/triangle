#version 330 core
out vec4 f_color;

in vec2 uv;
in vec4 color;

void main()
{
    //f_color = color;
    f_color = vec4(uv, 0.0, 1.0);
}
