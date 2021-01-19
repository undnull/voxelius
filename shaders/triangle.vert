#version 460

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec2 i_texcoord;

layout(location = 0) out vec2 o_texcoord;

void main(void)
{
    o_texcoord = i_texcoord;
    gl_Position = vec4(i_position, 1.0);
}
