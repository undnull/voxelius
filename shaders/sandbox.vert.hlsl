struct VSInput {
    float3 position : POSITION0;
};

struct VSOutput {
    float4 position : SV_POSITION;
};

cbuffer UBO0 : register(b0) {
    float4x4 model;
    float4 color;
};

void main(in VSInput vsi, out VSOutput vso)
{
    vso.position = model * float4(vsi.position, 1.0);
}
