/*
 * sandbox_fs.glsl
 * Created: 2021-01-22, 19:21:05.
 * Copyright (C) 2021, Kirill GPRB.
 */
#version 460

layout(location = 0) in vec2 i_texcoord;
layout(location = 0) out vec4 o_target;
layout(binding = 0) uniform sampler2D u_sampler;

void main(void)
{
    o_target = texture(u_sampler, i_texcoord);
}
