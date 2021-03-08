/*
 * sprite.frag.hlsl
 * Created: 2021-03-08, 22:59:26.
 * Copyright (C) 2021, Kirill GPRB.
 */

struct ps_input {
    float2 texcoord : TEXCOORD0;
};

sampler2D diffuse : register(S0);

float4 main(ps_input input) : SV_Target
{
    return tex2D(diffuse, input.texcoord);
    return float4(1.0, 1.0, 1.0, 1.0);
}
