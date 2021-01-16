/*
 * vertex.hh
 * Created: 2021-01-16, 22:11:46.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RENDER_VERTEX_HH
#define VOXELIUS_RENDER_VERTEX_HH 1
#include <voxelius/types.hh>

namespace render
{
    struct vertex final {
        float3 position = { 0.0f, 0.0f, 0.0f };
        float3 normal = { 0.0f, 0.0f, 0.0f };
        float2 texcoord = { 0.0f, 0.0f };
        float4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
    };
}

#endif
