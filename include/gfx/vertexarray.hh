/*
 * vertexarray.hh
 * Created: 2021-03-01, 21:13:22.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gfx/buffer.hh>

namespace gfx
{
class VertexArray final {
public:
    VertexArray();
    VertexArray(VertexArray &&rhs);
    VertexArray(const VertexArray &rhs) = delete;

    ~VertexArray();

    VertexArray &operator=(VertexArray &&rhs);
    VertexArray &operator=(const VertexArray &rhs) = delete;

    void bindElementBuffer(const Buffer &ebo);
    void bindVertexBuffer(const Buffer &vbo, unsigned int binding, size_t offset, size_t stride);

    void enableAttribute(unsigned int attrib);

    template<typename T>
    void setAttributeFormat(unsigned int attrib, size_t count, bool normalized);
    void setAttributeBinding(unsigned int attrib, unsigned int binding);

    inline constexpr unsigned int get() const
    {
        return vaobj;
    }

private:
    unsigned int vaobj;
};
} // namespace gfx
