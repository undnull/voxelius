/*
 * mesh.hh
 * Created: 2021-01-22, 22:40:49.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_CLIENT_MESH_HH
#define VOXELIUS_CLIENT_MESH_HH 1
#include <voxelius/client/gl/vao.hh>
#include <voxelius/types.hh>
#include <vector>

struct vertex final {
    vec3_t position = vec3_t(0.0, 0.0, 0.0);
    vec2_t texcoord = vec2_t(0.0, 0.0);
};

class Mesh final {
public:
    void clear();

    void add_vertex(const vertex &vertex);
    void add_index(unsigned int index);

    void update();

    inline const size_t get_num_vertices() const
    {
        return vertices.size();
    }

    inline const size_t get_num_indices() const
    {
        return indices.size();
    }

public:
    gl::VAO vao;

private:
    gl::Buffer vbo, ebo;
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
};

#endif
