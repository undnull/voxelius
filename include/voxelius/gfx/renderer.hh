/*
 * renderer.hh
 * Created: 2021-01-22, 23:06:41.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GFX_RENDERER_HH
#define VOXELIUS_GFX_RENDERER_HH 1
#include <voxelius/gfx/mesh.hh>
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>

namespace gfx::renderer
{
    void setup_view(int width, int height, float z_near, float z_far);
    void store_view();
    void restore_view();
    void use_2d_view(const vec3_t &cam_position, const quat_t &cam_rotation);
    void use_3d_view(const vec3_t &cam_position, const quat_t &cam_rotation);

    void set_fov(float fov);
    float get_fov();

    void clear_color(const vec3_t &color);
    void clear_color(const vec4_t &color);
    void clear(bool color = true, bool depth = false, bool stencil = false);

    // This should be removed as soon as the material system is implemented
    void bind_texture(const gl::Texture *texture, unsigned int unit);

    void render(const Mesh &mesh, const mat4x4_t &mm, const gl::Program *program);
}

namespace renderer = gfx::renderer;

#endif