/*
 * shader.hh
 * Created: 2021-01-19, 10:51:22.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_SHADER_HH
#define VOXELIUS_GL_SHADER_HH 1
#include <voxelius/gl/object.hh>
#include <voxelius/types.hh>

namespace gl
{
    class Shader : public Object {
    public:
        Shader(unsigned int type);
        virtual ~Shader();

        void create() override;
        void release() override;
        bool is_good() const override;

        void set_binary(const void *binary, size_t size);
        bool specialize(const char *entry);

        inline constexpr unsigned int get_type() const
        {
            return type;
        }

        inline constexpr unsigned int get_shader() const
        {
            return shader;
        }

        inline constexpr const char * get_info_log() const
        {
            return info_log;
        }
    
    private:
        unsigned int type;
        unsigned int shader;
        char *info_log;
    };

    class VertexShader final : public Shader {
    public:
        VertexShader();
    };

    class FragmentShader final : public Shader {
    public:
        FragmentShader();
    };
}

#endif
