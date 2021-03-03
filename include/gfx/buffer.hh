/*
 * buffer.hh
 * Created: 2021-03-01, 20:44:30.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

#include <glad/glad.h>

namespace gfx
{
class Buffer final {
public:
    Buffer();
    Buffer(Buffer &&rhs);
    Buffer(const Buffer &&rhs) = delete;

    ~Buffer();

    Buffer &operator=(Buffer &&rhs);
    Buffer &operator=(const Buffer &rhs) = delete;

    void resize(size_t new_size);
    void write(size_t offset, const void *data, size_t size);

    constexpr unsigned int get() const;

private:
    unsigned int buffer;
};

inline Buffer::Buffer()
{
    glCreateBuffers(1, &buffer);
}

inline Buffer::Buffer(Buffer &&rhs)
{
    buffer = rhs.buffer;
    rhs.buffer = 0;
}

inline Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}

inline Buffer &Buffer::operator=(Buffer &&rhs)
{
    Buffer copy(std::move(rhs));
    std::swap(copy.buffer, buffer);
    return *this;
}

inline void Buffer::resize(size_t new_size)
{
    glNamedBufferData(buffer, static_cast<GLsizeiptr>(new_size), nullptr, GL_STATIC_DRAW);
}

inline void Buffer::write(size_t offset, const void *data, size_t size)
{
    glNamedBufferSubData(buffer, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}

inline constexpr unsigned int Buffer::get() const
{
    return buffer;
}
} // namespace gfx
