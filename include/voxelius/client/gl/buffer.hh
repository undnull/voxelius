/*
 * buffer.hh
 * Created: 2021-01-19, 10:35:53.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_CLIENT_GL_BUFFER_HH
#define VOXELIUS_CLIENT_GL_BUFFER_HH 1
#include <voxelius/client/gl/object.hh>
#include <voxelius/types.hh>

namespace gl
{
    class Buffer final : public Object {
    public:
        Buffer();
        ~Buffer();

        void create() override;
        void release() override;
        bool is_good() const override;

        void set_data(const void *data, size_t size);

        inline constexpr unsigned int get_buffer() const
        {
            return buffer;
        }

    private:
        unsigned int buffer;
    };
}

#endif
