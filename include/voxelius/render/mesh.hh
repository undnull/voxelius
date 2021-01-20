/*
 * mesh.hh
 * Created: 2021-01-20, 15:28:33.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RENDER_MESH_HH
#define VOXELIUS_RENDER_MESH_HH 1
#include <voxelius/gl/vao.hh>
#include <voxelius/render/vertex.hh>
#include <vector>

class Mesh final {
public:
    Mesh();

    void clear();

    void add_vertex(const vertex &vertex);
    void add_index(unsigned int index);

    void update();

    size_t get_num_vertices() const;
    size_t get_num_indices() const;

public:
    gl::VAO vao;

private:
    gl::Buffer vbo, ebo;
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
};

#endif
