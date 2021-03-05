struct VS_INPUT {
    float2 position : POSITION0;
    float2 texcoord : TEXCOORD1;
};

struct VS_OUTPUT {
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

cbuffer transform : register(b0) {
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

VS_OUTPUT main(in VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = projection * view * model * float4(input.position, 0.0, 1.0);
    output.texcoord = input.texcoord;
    return output;
}
