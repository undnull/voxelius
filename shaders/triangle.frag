#version 440

layout(location = 0) in vec4 i_color;

layout(location = 0) out vec4 o_color;

void main(void)
{
    // frag -> fbo
    o_color = vec4(1.0);
}
