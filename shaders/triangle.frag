#version 460

layout(location = 0) in vec2 i_texcoord;

layout(location = 0) out vec4 o_color;

layout(binding = 0) uniform sampler2D u_sampler;

void main(void)
{
    o_color = texture(u_sampler, i_texcoord);
}
