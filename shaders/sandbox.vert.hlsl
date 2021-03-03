struct VS_INPUT {
    float2 position : POSITION0;
    float2 uv : TEXCOORD1;
};

struct VS_OUTPUT {
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

VS_OUTPUT main(in VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 0.0, 1.0);
    output.uv = input.uv;
    return output;
}
