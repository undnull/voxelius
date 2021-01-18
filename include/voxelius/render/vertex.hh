/*
 * vertex.hh
 * Created: 2021-01-18, 14:01:44.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RENDER_VERTEX_HH
#define VOXELIUS_RENDER_VERTEX_HH 1
#include <voxelius/types.hh>

namespace render
{
    struct vertex final {
        vec3_t position = { 0.0, 0.0, 0.0 };
        vec4_t color = { 1.0, 1.0, 1.0, 1.0 };
    };
}

#endif
