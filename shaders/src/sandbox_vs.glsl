/*
 * sandbox_vs.glsl
 * Created: 2021-01-22, 19:21:07.
 * Copyright (C) 2021, Kirill GPRB.
 */
#version 460

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec2 i_texcoord;
layout(location = 0) out vec2 o_texcoord;
layout(location = 0) uniform mat4x4 u_model;

void main(void)
{
    o_texcoord = i_texcoord;
    gl_Position = u_model * vec4(i_position, 1.0);
}
