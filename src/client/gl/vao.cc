/*
 * vao.cc
 * Created: 2021-01-19, 12:13:10.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/client/gl/vao.hh>

#include <glad/glad.h>

namespace gl
{
VAO::VAO() :
    vao(0)
{
    create();
}

VAO::~VAO()
{
    release();
}

void VAO::create()
{
    release();
    glCreateVertexArrays(1, &vao);
}

void VAO::release()
{
    if(vao) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
}

bool VAO::isGood() const
{
    return vao != 0;
}

void VAO::bindVBO(const Buffer &buffer, unsigned int binding_index, size_t offset, size_t stride)
{
    glVertexArrayVertexBuffer(vao, binding_index, buffer.getBuffer(), (GLintptr)offset, (GLsizei)stride);
}

void VAO::bindEBO(const Buffer &buffer)
{
    glVertexArrayElementBuffer(vao, buffer.getBuffer());
}

void VAO::enableAttrib(unsigned int attrib_index)
{
    glEnableVertexArrayAttrib(vao, attrib_index);
}

template<>
void VAO::setAttribFormat<float>(unsigned int attrib_index, size_t count, bool normalized)
{
    glVertexArrayAttribFormat(vao, attrib_index, (GLint)count, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE, 0);
}

void VAO::setAttribBinding(unsigned int attrib_index, unsigned int binding_index)
{
    glVertexArrayAttribBinding(vao, attrib_index, binding_index);
}
} // namespace gl
