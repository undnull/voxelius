/*
 * mesh.hh
 * Created: 2021-01-16, 22:11:02.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RENDER_MESH_HH
#define VOXELIUS_RENDER_MESH_HH 1
#include <voxelius/gl/buffer.hh>
#include <voxelius/gl/vao.hh>
#include <voxelius/render/vertex.hh>
#include <vector>

namespace render
{
    class Mesh final {
    public:
        Mesh();

        void clear();

        void add_vertex(const vertex &vertex);
        void add_index(unsigned int index);

        void update();

        size_t get_num_vertices() const;
        size_t get_num_indices() const;
    
        gl::VAO & get_vao();

    private:
        gl::VAO vao;
        gl::Buffer vbo, ebo;
        std::vector<vertex> vertices;
        std::vector<unsigned int> indices;
    };
}

#endif
