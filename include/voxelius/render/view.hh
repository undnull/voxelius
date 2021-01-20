/*
 * view.hh
 * Created: 2021-01-20, 15:07:28.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RENDER_VIEW_HH
#define VOXELIUS_RENDER_VIEW_HH 1
#include <voxelius/types.hh>

// A Source-like structure (CViewSetup) containing
// some basic values to properly generate a VP matrix.
// todo: make these to be in stack (push_3d_view, push_2d_view, pop_view)
struct view final {
    int top = 0;
    int left = 0;
    int width = 0;
    int height = 0;
    float aspect = 0.0;
    float fov = 0.0;
    float z_near = 0.0;
    float z_far = 0.0;
    vec3_t camera_position = vec3_t();
    quat_t camera_rotation = quat_t();
    mat4x4_t matrix = mat4x4_t(1.0);
};

#endif
