#version 440

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec4 i_color;

layout(location = 0) out vec4 o_color;

layout(location = 0) uniform mat4x4 u_proj;
layout(location = 1) uniform mat4x4 u_modl;
layout(location = 2) uniform mat4x4 u_view;

void main(void)
{
    // vert -> frag
    o_color = i_color;

    // vert ->
    gl_Position = vec4(i_position, 1.0);
}
