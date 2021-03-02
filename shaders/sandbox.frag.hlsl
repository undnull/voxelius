cbuffer __cb_0 : register(b0) {
    float4x4 model;
    float4 color;
};

float4 main() : SV_TARGET
{
    return color;
}
