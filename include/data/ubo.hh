/*
 * ubo.hh
 * Created: 2021-03-05, 14:21:48.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace data
{
struct alignas(16) ubo_transform final {
    float4x4_t model = float4x4_t(1.0f);
    float4x4_t view = float4x4_t(1.0f);
    float4x4_t projection = float4x4_t(1.0f);
};
} // namespace data
