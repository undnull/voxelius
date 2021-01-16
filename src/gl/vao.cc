/*
 * vao.cc
 * Created: 2021-01-16, 19:11:15.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/vao.hh>
#include <glad/glad.h>

namespace gl
{
    VAO::VAO()
    {
        glGenVertexArrays(1, &vao);
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &vao);
    }

    unsigned int VAO::get_vao() const
    {
        return vao;
    }

    void VAO::enable_attrib(unsigned int index) const
    {
        glEnableVertexAttribArray(index);
    }

    void VAO::set_attrib_ptr_float(unsigned int index, size_t stride, size_t count, size_t offset) const
    {
        glVertexAttribPointer(index, (GLint)count, GL_FLOAT, GL_FALSE, (GLsizei)stride, (const void *)offset);
    }

    void VAO::bind() const
    {
        glBindVertexArray(vao);
    }

    void VAO::unbind() const
    {
        glBindVertexArray(0);
    }
}
