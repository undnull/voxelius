struct VS_INPUT {
    float3 position : POSITION0;
    float2 uv : TEXCOORD1;
};

struct VS_OUTPUT {
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

cbuffer __ubo_0 : register(b0) {
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

VS_OUTPUT main(in VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = projection * view * model * float4(input.position, 1.0f);
    output.uv = input.uv;
    return output;
}
