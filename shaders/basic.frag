#version 330 core
out vec4 f_color;

in vec2 uv;
in vec4 color;

void main()
{
    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    f_color = vec4(uv, 0.0, 1.0);
}
