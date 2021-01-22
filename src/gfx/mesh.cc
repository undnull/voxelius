/*
 * mesh.cc
 * Created: 2021-01-22, 22:52:16.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gfx/mesh.hh>

namespace gfx
{
    void Mesh::clear()
    {
        vertices.clear();
        indices.clear();
    }

    void Mesh::add_vertex(const vertex &vertex)
    {
        vertices.push_back(vertex);
    }

    void Mesh::add_index(unsigned int index)
    {
        indices.push_back(index);
    }

    void Mesh::update()
    {
        vbo.set_data(vertices.data(), sizeof(vertex) * vertices.size());
        ebo.set_data(indices.data(), sizeof(unsigned int) * indices.size());

        vao.bind_vbo(vbo, 0, offsetof(vertex, position), sizeof(vertex));
        vao.bind_vbo(vbo, 1, offsetof(vertex, texcoord), sizeof(vertex));
        vao.bind_ebo(ebo);

        vao.enable_attrib(0);
        vao.enable_attrib(1);

        vao.set_attrib_format<float>(0, 3, false);
        vao.set_attrib_format<float>(1, 2, false);

        vao.set_attrib_binding(0, 0);
        vao.set_attrib_binding(1, 1);
    }
}
