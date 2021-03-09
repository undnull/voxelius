/*
 * sprite.vert.hlsl
 * Created: 2021-03-08, 22:41:30.
 * Copyright (C) 2021, Kirill GPRB.
 */

struct vs_input {
    float2 position : POSITION;
    float2 texcoord : TEXCOORD1;
    int instance_id : SV_InstanceID;
};

struct vs_output {
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD1;
};

cbuffer ubo : register(b0) {
    row_major float4x4 projection;
    row_major float4x4 scale;
    row_major float4x4 view;
};

row_major StructuredBuffer<float4x4> ssbo : register(u0);

vs_output main(vs_input input)
{
    vs_output output;

    // output.position = projection * view * (transform[input.instance_id] * scale) * float4(input.position, 0.0, 1.0);
    // output.position = projection * view * scale * float4(input.position, 0.0, 1.0);
    output.position = projection * view * (ssbo[input.instance_id] * scale) * float4(input.position, 0.0, 1.0);
    // output.position = mul(output.position, transform[input.instance_id]);
    // output.position = mul(output.position, scale);
    // output.position = mul(output.position, view);
    // output.position = mul(output.position, projection);

    output.texcoord = input.texcoord;

    return output;
}
