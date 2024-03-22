#version 330 core
layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec4 v_color;

out vec2 uv;
out vec4 color;

void main()
{
    gl_Position = vec4(v_pos, 0.0, 1.0);
    color = v_color;
    uv = v_uv;
}
