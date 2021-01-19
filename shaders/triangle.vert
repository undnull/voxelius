#version 460

layout(location = 0) in vec3 position;
layout(location = 0) out vec3 opos;

void main(void)
{
    opos = position;
    gl_Position = vec4(position, 1.0);
}
