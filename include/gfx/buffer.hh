/*
 * buffer.hh
 * Created: 2021-03-01, 20:44:30.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

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

    inline constexpr unsigned int get() const
    {
        return buffer;
    }

private:
    unsigned int buffer;
};
} // namespace gfx
