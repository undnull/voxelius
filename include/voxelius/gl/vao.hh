/*
 * vao.hh
 * Created: 2021-01-16, 18:57:59.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_VAO_HH
#define VOXELIUS_GL_VAO_HH

namespace gl
{
    class VAO final {
    public:
        typedef unsigned int index_t;

    public:
        VAO();
        ~VAO();

        unsigned int get_vao() const;

        void enable_attrib(unsigned int index) const;

        void set_attrib_ptr_d(unsigned int index, size_t stride, size_t count, size_t offset) const;

        void bind() const;
        void unbind() const;

    private:
        unsigned int vao;
    };
}

#endif
