/*
 * program.hh
 * Created: 2021-01-16, 17:29:37.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_PROGRAM_HH
#define VOXELIUS_GL_PROGRAM_HH 1
#include <voxelius/gl/shader.hh>
#include <voxelius/types.hh>

namespace gl
{
    class Program final {
    public:
        Program();
        ~Program();

        unsigned int get_program() const;

        void attach(const Shader &shader) const;

        bool try_link();
        const char * get_info_log() const;

        void bind() const;
        void unbind() const;

        int find_uniform(const char *name) const;

        void set_uniform(int location, const int value) const;
        void set_uniform(int location, const float value) const;
        void set_uniform(int location, const double value) const;
        void set_uniform(int location, const vec2_t &value) const;
        void set_uniform(int location, const vec3_t &value) const;
        void set_uniform(int location, const vec4_t &value) const;
        void set_uniform(int location, const mat4x4_t &value) const;

    private:
        unsigned int program;
        char *info_log;
    };
}

#endif
