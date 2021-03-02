struct VS_INPUT {
    float3 position : POSITION0;
};

struct VS_OUTPUT {
    float4 position : SV_POSITION;
};

cbuffer __cb_0 : register(b0) {
    float4x4 model;
    float4 color;
};

VS_OUTPUT main(in VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = model * float4(input.position, 1.0);
    return output;
}
