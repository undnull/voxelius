/*
 * vao.hh
 * Created: 2021-01-19, 11:56:58.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_VAO_HH
#define VOXELIUS_GL_VAO_HH 1
#include <voxelius/gl/buffer.hh>

namespace gl
{
    class VAO final : public Object {
    public:
        VAO();
        ~VAO();

        void create() override;
        void release() override;
        bool is_good() const override;

        void bind_vbo(const Buffer &buffer, unsigned int binding_index, size_t offset, size_t stride);
        void bind_ebo(const Buffer &buffer);

        void enable_attrib(unsigned int attrib_index);
        template<typename T>
        void set_attrib_format(unsigned int attrib_index, size_t count, bool normalized);
        void set_attrib_binding(unsigned int attrib_index, unsigned int binding_index);

        inline constexpr unsigned int get_vao() const
        {
            return vao;
        }

    private:
        unsigned int vao;
    };
}

#endif
