/*
 * sandbox.frag
 * Created: 2021-01-19, 22:30:24.
 * Copyright (C) 2021, Kirill GPRB.
 */
#version 460

layout(location = 0) in vec2 i_texcoord;

layout(location = 0) out vec4 o_color;

layout(binding = 0) uniform sampler2D u_sampler;

void main(void)
{
    o_color = texture(u_sampler, i_texcoord);
}
