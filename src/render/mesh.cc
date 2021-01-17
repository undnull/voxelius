/*
 * mesh.cc
 * Created: 2021-01-16, 22:16:05.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/render/mesh.hh>
#include <glad/glad.h>

namespace render
{
    Mesh::Mesh() : vao(), vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER), vertices(), indices()
    {

    }

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
        // fixme: check for the index validity???
        indices.push_back(index);
    }

    void Mesh::update()
    {
        vao.bind();

        vbo.bind();
        vbo.set_data(vertices.data(), sizeof(vertex) * vertices.size());

        ebo.bind();
        ebo.set_data(indices.data(), sizeof(unsigned int) * indices.size());

        vao.enable_attrib(0);
        vao.set_attrib_ptr_d(0, sizeof(vertex), 3, offsetof(vertex, position));
        vao.enable_attrib(1);
        vao.set_attrib_ptr_d(1, sizeof(vertex), 3, offsetof(vertex, normal));
        vao.enable_attrib(2);
        vao.set_attrib_ptr_d(2, sizeof(vertex), 2, offsetof(vertex, texcoord));
        vao.enable_attrib(3);
        vao.set_attrib_ptr_d(3, sizeof(vertex), 4, offsetof(vertex, color));

        vao.unbind();
    }

    size_t Mesh::get_num_vertices() const
    {
        return vertices.size();
    }

    size_t Mesh::get_num_indices() const
    {
        return indices.size();
    }

    gl::VAO & Mesh::get_vao()
    {
        return vao;
    }
}
