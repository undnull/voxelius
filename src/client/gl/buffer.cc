/*
 * buffer.cc
 * Created: 2021-01-19, 10:40:37.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/client/gl/buffer.hh>
#include <glad/glad.h>

namespace gl
{
    Buffer::Buffer() : buffer(0)
    {
        create();
    }

    Buffer::~Buffer()
    {
        release();
    }

    void Buffer::create()
    {
        release();
        glCreateBuffers(1, &buffer);
    }

    void Buffer::release()
    {
        if(buffer) {
            glDeleteBuffers(1, &buffer);
            buffer = 0;
        }
    }

    bool Buffer::is_good() const
    {
        return buffer != 0;
    }

    void Buffer::set_data(const void *data, size_t size)
    {
        glNamedBufferData(buffer, (GLsizeiptr)size, data, GL_STATIC_DRAW);
    }
}
