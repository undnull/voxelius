#version 460

layout(location = 0) in vec3 position;
layout(location = 0) out vec4 target;

void main(void)
{
    target = vec4(position.yxy, 1.0);
}
