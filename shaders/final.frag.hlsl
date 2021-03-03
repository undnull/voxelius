uniform sampler2D tex : register(s0);

float4 main(in float2 texcoord : TEXCOORD0) : SV_TARGET
{
    return 1.0 - tex2D(tex, texcoord);
}
