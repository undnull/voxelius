/*
 * vertex_array.hh
 * Created: 2021-03-01, 21:13:22.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gfx/buffer.hh>

namespace gfx
{
template<typename T>
constexpr unsigned int ATTRIBUTE_FORMAT = 0;
template<>
constexpr unsigned int ATTRIBUTE_FORMAT<float> = GL_FLOAT;

class VertexArray {
public:
    VertexArray();
    VertexArray(VertexArray &&rhs);
    VertexArray(const VertexArray &rhs) = delete;

    virtual ~VertexArray();

    VertexArray &operator=(VertexArray &&rhs);
    VertexArray &operator=(const VertexArray &rhs) = delete;

    void bindElementBuffer(const Buffer &ebo);
    void bindVertexBuffer(const Buffer &vbo, unsigned int binding, size_t offset, size_t stride);

    void enableAttribute(unsigned int attrib);

    template<typename T>
    void setAttributeFormat(unsigned int attrib, size_t count, bool normalized);
    void setAttributeBinding(unsigned int attrib, unsigned int binding);

    constexpr unsigned int get() const;

private:
    unsigned int vaobj;
};

inline VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &vaobj);
}

inline VertexArray::VertexArray(VertexArray &&rhs)
{
    vaobj = rhs.vaobj;
    rhs.vaobj = 0;
}

inline VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vaobj);
}

inline VertexArray &VertexArray::operator=(VertexArray &&rhs)
{
    VertexArray copy(std::move(rhs));
    std::swap(copy.vaobj, vaobj);
    return *this;
}

inline void VertexArray::bindElementBuffer(const Buffer &ebo)
{
    glVertexArrayElementBuffer(vaobj, ebo.get());
}

inline void VertexArray::bindVertexBuffer(const Buffer &vbo, unsigned int binding, size_t offset, size_t stride)
{
    glVertexArrayVertexBuffer(vaobj, binding, vbo.get(), static_cast<GLintptr>(offset), static_cast<GLsizei>(stride));
}

inline void VertexArray::enableAttribute(unsigned int attrib)
{
    glEnableVertexArrayAttrib(vaobj, attrib);
}

template<typename T>
inline void VertexArray::setAttributeFormat(unsigned int attrib, size_t count, bool normalized)
{
    glVertexArrayAttribFormat(vaobj, attrib, static_cast<GLint>(count), ATTRIBUTE_FORMAT<T>, normalized ? GL_TRUE : GL_FALSE, 0);
}

inline void VertexArray::setAttributeBinding(unsigned int attrib, unsigned int binding)
{
    glVertexArrayAttribBinding(vaobj, attrib, binding);
}

inline constexpr unsigned int VertexArray::get() const
{
    return vaobj;
}
} // namespace gfx
