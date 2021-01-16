/*
 * buffer.cc
 * Created: 2021-01-16, 18:25:00.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/buffer.hh>
#include <glad/glad.h>

namespace gl
{
    Buffer::Buffer(unsigned int target) : target(target)
    {
        glGenBuffers(1, &buffer);
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &buffer);
    }

    unsigned int Buffer::get_buffer() const
    {
        return buffer;
    }

    unsigned int Buffer::get_target() const
    {
        return target;
    }

    void Buffer::set_data(const void *data, size_t size) const
    {
        glBufferData(target, (GLsizeiptr)size, data, GL_STATIC_DRAW);
    }

    void Buffer::bind() const
    {
        glBindBuffer(target, buffer);
    }

    void Buffer::unbind() const
    {
        glBindBuffer(target, 0);
    }
}
