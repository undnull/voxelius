/*
 * tile.hh
 * Created: 2021-03-03, 20:34:34.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace data
{
struct tile final {
    float top = 0.0f;
    float left = 0.0f;
    float bottom = 0.0f;
    float right = 0.0f;
};
} // namespace data
