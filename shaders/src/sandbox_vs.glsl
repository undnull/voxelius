/*
 * sandbox_vs.glsl
 * Created: 2021-01-22, 19:21:07.
 * Copyright (C) 2021, Kirill GPRB.
 */
#version 460

layout(location = 0) in vec3 position;

out gl_PerVertex {
    vec4 gl_Position;
};

void main(void)
{
    gl_Position = vec4(position, 1.0);
}
