/*
 * sprite_renderer.hh
 * Created: 2021-03-08, 18:48:54.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <render/common.hh>

namespace render
{
class SpriteRenderer final {
public:
    struct alignas(16) ubo0_s final {
        float4x4_t projection;
        float4x4_t scale;
        float4x4_t view;
    };

public:
    SpriteRenderer(int width, int height);

    void setView(const data::View &view);
    void draw(const std::vector<data::Transform> &transforms, const gfx::Texture &texture, const float2_t &size);

private:
    gfx::VertexShader vert;
    gfx::FragmentShader frag;
    gfx::Pipeline pipeline;

    gfx::Buffer vbo, ebo;
    gfx::VertexArray vao;

    gfx::Buffer ubo0;
    gfx::Buffer ubo1;

    std::vector<float4x4_t> instances;
};
} // namespace render
