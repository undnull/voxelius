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
enum class BufferUsage {
    STATIC,
    STREAM,
    DYNAMIC,
};

template<BufferUsage T>
constexpr GLenum BUFFER_USAGE = 0;
template<>
constexpr GLenum BUFFER_USAGE<BufferUsage::STATIC> = GL_STATIC_DRAW;
template<>
constexpr GLenum BUFFER_USAGE<BufferUsage::STREAM> = GL_STREAM_DRAW;
template<>
constexpr GLenum BUFFER_USAGE<BufferUsage::DYNAMIC> = GL_DYNAMIC_DRAW;

class Buffer final {
public:
    Buffer();
    Buffer(Buffer &&rhs);
    Buffer(const Buffer &&rhs) = delete;

    ~Buffer();

    Buffer &operator=(Buffer &&rhs);
    Buffer &operator=(const Buffer &rhs) = delete;

    template<BufferUsage T>
    void storage(size_t size);
    void subData(size_t offset, const void *data, size_t size);

    constexpr GLuint get() const;

private:
    GLuint buffer;
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

template<BufferUsage T>
inline void Buffer::storage(size_t size)
{
    glNamedBufferData(buffer, static_cast<GLsizeiptr>(size), nullptr, BUFFER_USAGE<T>);
}

inline void Buffer::subData(size_t offset, const void *data, size_t size)
{
    glNamedBufferSubData(buffer, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}

inline constexpr GLuint Buffer::get() const
{
    return buffer;
}
} // namespace gfx
