/*
 * maprenderer.hh
 * Created: 2021-03-05, 14:25:12.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <data/map.hh>

namespace render
{
class MapRenderer final {
public:
    MapRenderer(int width, int height);
    void setView(const float4x4_t &view);
    void render(const data::Map &map);

private:
    gfx::Buffer transform;
};
} // namespace render
