/*
 * map.hh
 * Created: 2021-03-05, 12:32:09.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gfx/pipeline.hh>
#include <gfx/texture.hh>
#include <gfx/vertex_array.hh>
#include <util/fs.hh>

namespace data
{
class Map final {
public:
    struct layer final {
        gfx::VertexShader vertex;
        gfx::FragmentShader fragment;
        gfx::Pipeline pipeline;
        std::unordered_map<unsigned int, gfx::Texture> textures;
        gfx::Buffer geometry_vbo;
        gfx::Buffer geometry_ebo;
        gfx::VertexArray geometry_vao;
        size_t geometry_count;
    };

public:
    bool loadFromFile(const fs::path &path);

    constexpr const std::vector<layer> &getLayers() const;

private:
    std::vector<layer> layers;
};

inline constexpr const std::vector<Map::layer> &Map::getLayers() const
{
    return layers;
}
} // namespace data
