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
        vec3_t position = { 0.0, 0.0, 0.0 };
        vec3_t normal = { 0.0, 0.0, 0.0 };
        vec2_t texcoord = { 0.0, 0.0 };
        vec4_t color = { 1.0, 1.0, 1.0, 1.0 };
    };
}

#endif
