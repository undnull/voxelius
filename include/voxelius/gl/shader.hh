/*
 * shader.hh
 * Created: 2021-01-16, 17:21:16.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_SHADER_HH
#define VOXELIUS_GL_SHADER_HH 1

namespace gl
{
    class Shader {
    public:
        Shader(const unsigned int type);
        virtual ~Shader();

        unsigned int get_shader() const;

        void set_source(const char *source) const;

        bool try_compile();
        const char * get_info_log() const;

    private:
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
