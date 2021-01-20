/*
 * vertex.hh
 * Created: 2021-01-20, 15:16:17.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RENDER_VERTEX_HH
#define VOXELIUS_RENDER_VERTEX_HH 1
#include <voxelius/types.hh>

struct vertex final {
    vec3_t position = vec3_t(0.0, 0.0, 0.0);
    vec2_t texcoord = vec2_t(0.0, 0.0);
};

#endif
