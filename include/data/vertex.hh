/*
 * vertex.hh
 * Created: 2021-03-05, 12:01:05.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace data
{
struct vertex {
    float2_t position = { 0.0f, 0.0f };
    float2_t texcoord = { 0.0f, 0.0f };
};
} // namespace data
