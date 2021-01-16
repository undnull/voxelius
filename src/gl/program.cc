/*
 * program.cc
 * Created: 2021-01-16, 17:31:41.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/program.hh>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace gl
{
    Program::Program() : program(glCreateProgram()), info_log(nullptr)
    {

    }

    Program::~Program()
    {
        glDeleteProgram(program);
    }

    unsigned int Program::get_program() const
    {
        return program;
    }

    void Program::attach(const Shader &shader) const
    {
        glAttachShader(program, shader.get_shader());
    }

    bool Program::try_link()
    {
        if(info_log) {
            delete[] info_log;
            info_log = nullptr;
        }

        int success;
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if(success != GL_TRUE) {
            int size;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);

            info_log = new char[(size_t)size + 1];
            info_log[size] = 0;
            
            glGetProgramInfoLog(program, size, 0, info_log);
            return false;
        }

        return true;
    }

    const char * Program::get_info_log() const
    {
        return info_log;
    }

    void Program::bind() const
    {
        glUseProgram(program);
    }

    void Program::unbind() const
    {
        glUseProgram(0);
    }

    int Program::find_uniform(const char *name) const
    {
        return glGetUniformLocation(program, name);
    }

    void Program::set_uniform(int location, const int value) const
    {
        glProgramUniform1i(program, location, value);
    }

    void Program::set_uniform(int location, const float value) const
    {
        glProgramUniform1f(program, location, value);
    }

    void Program::set_uniform(int location, const float2 &value) const
    {
        glProgramUniform2fv(program, location, 1, glm::value_ptr(value));
    }

    void Program::set_uniform(int location, const float3 &value) const
    {
        glProgramUniform3fv(program, location, 1, glm::value_ptr(value));
    }

    void Program::set_uniform(int location, const float4 &value) const
    {
        glProgramUniform4fv(program, location, 1, glm::value_ptr(value));
    }

    void Program::set_uniform(int location, const float4x4 &value) const
    {
        glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, glm::value_ptr(value));
    }
}
