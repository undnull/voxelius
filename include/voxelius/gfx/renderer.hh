/*
 * renderer.hh
 * Created: 2021-01-22, 23:06:41.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GFX_RENDERER_HH
#define VOXELIUS_GFX_RENDERER_HH 1
#include <voxelius/gfx/mesh.hh>
#include <voxelius/gfx/view.hh>
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>

namespace gfx::renderer
{
    void push_2d_view(int width, int height, int top = 0, int left = 0, float z_near = 0.1, float z_far = 1.0);
    void push_3d_view(int width, int height, float fov, float z_near = 0.1, float z_far = 1.0);
    void pop_view();

    // This should be removed as soon as the material system is implemented
    void bind_texture(const gl::Texture *texture, unsigned int unit);

    void render(const Mesh &mesh, const mat4x4_t &mm, const gl::Program *program);
}

#endif
