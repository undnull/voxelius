/*
 * program.cc
 * Created: 2021-01-19, 11:48:54.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/program.hh>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace gl
{
    Program::Program() : program(0), info_log(nullptr)
    {
        create();
    }

    Program::~Program()
    {
        if(info_log)
            delete[] info_log;
        release();
    }

    void Program::create()
    {
        release();
        program = glCreateProgram();
    }

    void Program::release()
    {
        if(program) {
            glDeleteProgram(program);
            program = 0;
        }
    }

    bool Program::is_good() const
    {
        return program != 0;
    }

    void Program::attach(const Shader &shader)
    {
        glAttachShader(program, shader.get_shader());
    }

    bool Program::link()
    {
        if(info_log) {
            delete[] info_log;
            info_log = nullptr;
        }

        int success;
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if(success == GL_FALSE) {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            info_log = new char[(size_t)length + 1];
            info_log[(size_t)length] = 0;
            glGetProgramInfoLog(program, length, 0, info_log);

            return false;
        }

        return true;
    }

    void Program::bind() const
    {
        glUseProgram(program);
    }

    void Program::unbind() const
    {
        glUseProgram(0);
    }

    void Program::set_uniform(int location, const int value) const
    {
        glProgramUniform1i(program, location, value);
    }

    void Program::set_uniform(int location, const float value) const
    {
        glProgramUniform1f(program, location, value);
    }

    void Program::set_uniform(int location, const vec2_t &value) const
    {
        glProgramUniform2fv(program, location, 1, glm::value_ptr(value));
    }

    void Program::set_uniform(int location, const vec3_t &value) const
    {
        glProgramUniform3fv(program, location, 1, glm::value_ptr(value));
    }

    void Program::set_uniform(int location, const vec4_t &value) const
    {
        glProgramUniform4fv(program, location, 1, glm::value_ptr(value));
    }

    void Program::set_uniform(int location, const mat4x4_t &value) const
    {
        glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, glm::value_ptr(value));
    }
}
