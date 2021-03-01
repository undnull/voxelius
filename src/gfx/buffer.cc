/*
 * buffer.cc
 * Created: 2021-03-01, 20:57:57.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <gfx/buffer.hh>

#include <glad/glad.h>

#include <utility>

namespace gfx
{
Buffer::Buffer()
{
    glCreateBuffers(1, &buffer);
}

Buffer::Buffer(Buffer &&rhs)
{
    buffer = rhs.buffer;
    rhs.buffer = 0;
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}

Buffer &Buffer::operator=(Buffer &&rhs)
{
    Buffer copy(std::move(rhs));
    std::swap(copy.buffer, buffer);
    return *this;
}

void Buffer::resize(size_t new_size)
{
    glNamedBufferData(buffer, static_cast<GLsizeiptr>(new_size), nullptr, GL_STATIC_DRAW);
}

void Buffer::write(size_t offset, const void *data, size_t size)
{
    glNamedBufferSubData(buffer, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}
} // namespace gfx
