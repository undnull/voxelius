/*
 * final.hh
 * Created: 2021-03-03, 13:38:46.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gfx/framebuffer.hh>
#include <gfx/pipeline.hh>
#include <gfx/vertexarray.hh>

namespace render
{
class FinalRenderer final {
public:
    FinalRenderer(int width, int height);
    void render();

    constexpr const gfx::Framebuffer &getFramebuffer() const;

private:
    gfx::Buffer vbo;
    gfx::Buffer ebo;
    gfx::VertexArray vao;
    gfx::Framebuffer fbo;
    gfx::Texture color;
    gfx::VertexShader vs;
    gfx::FragmentShader fs;
    gfx::Pipeline pipeline;
};

inline constexpr const gfx::Framebuffer &FinalRenderer::getFramebuffer() const
{
    return fbo;
}
} // namespace render
