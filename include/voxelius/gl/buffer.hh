/*
 * buffer.hh
 * Created: 2021-01-19, 10:35:53.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_BUFFER_HH
#define VOXELIUS_GL_BUFFER_HH 1
#include <voxelius/gl/object.hh>
#include <voxelius/types.hh>

namespace gl
{
class Buffer final : public Object {
public:
    Buffer();
    ~Buffer();

    void create() override;
    void release() override;
    bool isGood() const override;

    void setData(const void *data, size_t size);

    inline constexpr unsigned int getBuffer() const
    {
        return buffer;
    }

private:
    unsigned int buffer;
};
} // namespace gl

#endif
