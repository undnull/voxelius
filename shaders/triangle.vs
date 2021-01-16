/*
 * triangle.vs
 * Created: 2021-01-16, 21:52:34.
 * Copyright (C) 2021, Kirill GPRB.
 */
#version 440

layout(location = 0) in vec3 position;
layout(location = 0) out vec3 stub;

void main(void)
{
    stub = position;
    gl_Position = vec4(position, 1.0);
}
