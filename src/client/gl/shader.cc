/*
 * shader.cc
 * Created: 2021-01-19, 11:15:39.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/client/gl/shader.hh>
#include <glad/glad.h>

namespace gl
{
    Shader::Shader(unsigned int type) : type(type), shader(0), info_log(nullptr)
    {
        create();
    }

    Shader::~Shader()
    {
        if(info_log)
            delete[] info_log;
        release();
    }

    void Shader::create()
    {
        release();
        shader = glCreateShader(type);
    }

    void Shader::release()
    {
        if(shader) {
            glDeleteShader(shader);
            shader = 0;
        }
    }

    bool Shader::is_good() const
    {
        return shader != 0;
    }

    void Shader::set_binary(const void *binary, size_t size)
    {
        // GL4.6: SPIR-V shaders
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary, (GLsizei)size);
    }

    bool Shader::specialize(const char *entry)
    {
        if(info_log) {
            delete[] info_log;
            info_log = nullptr;
        }

        int success;
        glSpecializeShader(shader, entry, 0, 0, nullptr);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(success == GL_FALSE) {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            info_log = new char[length];
            glGetShaderInfoLog(shader, length, 0, info_log);

            return false;
        }

        return true;
    }

    VertexShader::VertexShader() : Shader(GL_VERTEX_SHADER)
    {

    }

    FragmentShader::FragmentShader() : Shader(GL_FRAGMENT_SHADER)
    {
        
    }
}
