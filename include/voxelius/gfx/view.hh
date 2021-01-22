/*
 * view.hh
 * Created: 2021-01-22, 22:29:06.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GFX_VIEW_HH
#define VOXELIUS_GFX_VIEW_HH 1
#include <voxelius/types.hh>

namespace gfx
{
    struct view final {
        int top = 0;
        int left = 0;
        int width = 0;
        int height = 0;
        float aspect = 0.0;
        float z_far = 0.0;
        float z_near = 0.0;
        vec3_t position = vec3_t(0.0, 0.0, 0.0);
        quat_t rotation = quat_t(0.0, 0.0, 0.0, 0.0);
    };
}

#endif
