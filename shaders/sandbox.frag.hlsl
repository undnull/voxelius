struct PS_INPUT {
    float2 texcoord : TEXCOORD0;
};

uniform sampler2D t : register(s0);

float4 main(in PS_INPUT input) : SV_TARGET
{
    return tex2D(t, input.texcoord);
}
