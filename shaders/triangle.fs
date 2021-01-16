/*
 * triangle.fs
 * Created: 2021-01-16, 21:51:36.
 * Copyright (C) 2021, Kirill GPRB.
 */
#version 440

layout(location = 0) out vec4 fs_target;
layout(location = 0) in vec3 stub;

void main(void)
{
    //fs_target = vec4(0.0, 1.0, 0.0, 1.0);
    fs_target = vec4(stub.xyy, 1.0);
}
