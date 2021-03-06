/*
 * map_renderer.hh
 * Created: 2021-03-05, 14:25:12.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <data/map.hh>
#include <gfx/framebuffer.hh>

namespace render
{
class MapRenderer final {
public:
    MapRenderer(int width, int height);
    void setView(const float4x4_t &view);
    void render(const data::Map &map);
    const float2_t &getTargetSize() const;
    const gfx::Texture &getColorTarget() const;

private:
    const float2_t target_size;
    gfx::Framebuffer framebuffer;
    gfx::Texture color_target;
    gfx::Buffer transform;
};

inline const float2_t &MapRenderer::getTargetSize() const
{
    return target_size;
}

inline const gfx::Texture &MapRenderer::getColorTarget() const
{
    return color_target;
}
} // namespace render
