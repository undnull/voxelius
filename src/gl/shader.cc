/*
 * shader.cc
 * Created: 2021-01-16, 17:24:50.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/shader.hh>
#include <glad/glad.h>

namespace gl
{
    Shader::Shader(const unsigned int type) : shader(glCreateShader(type)), info_log(nullptr)
    {

    }

    Shader::~Shader()
    {
        glDeleteProgram(shader);
        if(info_log)
            delete[] info_log;
    }

    unsigned int Shader::get_shader() const
    {
        return shader;
    }

    void Shader::set_source(const char *source) const
    {
        glShaderSource(shader, 1, &source, 0);
    }

    bool Shader::try_compile()
    {
        if(info_log) {
            delete[] info_log;
            info_log = nullptr;
        }

        int success;
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(success != GL_TRUE) {
            int size;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

            info_log = new char[(size_t)size + 1];
            info_log[size] = 0;
            
            glGetShaderInfoLog(shader, size, 0, info_log);
            return false;
        }

        return true;
    }

    const char * Shader::get_info_log() const
    {
        return info_log;
    }

    VertexShader::VertexShader() : Shader(GL_VERTEX_SHADER)
    {

    }

    FragmentShader::FragmentShader() : Shader(GL_FRAGMENT_SHADER)
    {

    }
}
