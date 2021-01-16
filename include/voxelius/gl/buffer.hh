/*
 * buffer.hh
 * Created: 2021-01-16, 18:03:59.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_BUFFER_HH
#define VOXELIUS_GL_BUFFER_HH 1
#include <stddef.h>

namespace gl
{
    class Buffer {
    public:
        Buffer(unsigned int target);
        virtual ~Buffer();
    
        unsigned int get_buffer() const;
        unsigned int get_target() const;
        
        // fixme: set_static_data and set_dynamic_data instead?
        void set_data(const void *data, size_t size) const;

        void bind() const;
        void unbind() const;

    private:
        unsigned int buffer;
        unsigned int target;
    };
}

#endif
