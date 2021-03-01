/*
 * vertexarray.cc
 * Created: 2021-03-01, 21:17:20.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <gfx/vertexarray.hh>

#include <glad/glad.h>

#include <utility>

namespace gfx
{
VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &vaobj);
}

VertexArray::VertexArray(VertexArray &&rhs)
{
    vaobj = rhs.vaobj;
    rhs.vaobj = 0;
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vaobj);
}

VertexArray &VertexArray::operator=(VertexArray &&rhs)
{
    VertexArray copy(std::move(rhs));
    std::swap(copy.vaobj, vaobj);
    return *this;
}

void VertexArray::bindElementBuffer(const Buffer &ebo)
{
    glVertexArrayElementBuffer(vaobj, ebo.get());
}

void VertexArray::bindVertexBuffer(const Buffer &vbo, unsigned int binding, size_t offset, size_t stride)
{
    glVertexArrayVertexBuffer(vaobj, binding, vbo.get(), static_cast<GLintptr>(offset), static_cast<GLsizei>(stride));
}

void VertexArray::enableAttribute(unsigned int attrib)
{
    glEnableVertexArrayAttrib(vaobj, attrib);
}

template<>
void VertexArray::setAttributeFormat<float>(unsigned int attrib, size_t count, bool normalized)
{
    glVertexArrayAttribFormat(vaobj, attrib, static_cast<GLint>(count), GL_FLOAT, normalized ? GL_TRUE : GL_FALSE, 0);
}

void VertexArray::setAttributeBinding(unsigned int attrib, unsigned int binding)
{
    glVertexArrayAttribBinding(vaobj, attrib, binding);
}
} // namespace gfx
