/*
 * shader.cc
 * Created: 2021-03-01, 20:58:05.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <gfx/shader.hh>

#include <glad/glad.h>

namespace gfx
{
Shader::Shader(unsigned int type) : type(type), program(glCreateProgram()), info_log(nullptr)
{
    glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
}

Shader::Shader(Shader &&rhs)
{
    type = rhs.type;
    program = rhs.program;
    info_log = rhs.info_log;
    rhs.type = 0;
    rhs.program = 0;
    rhs.info_log = nullptr;
}

Shader::~Shader()
{
    if(info_log)
        delete[] info_log;
    glDeleteProgram(program);
}

Shader &Shader::operator=(Shader &&rhs)
{
    Shader copy(std::move(rhs));
    std::swap(copy.type, type);
    std::swap(copy.program, program);
    std::swap(copy.info_log, info_log);
    return *this;
}

bool Shader::link(const void *binary, size_t size)
{
    int status;

    unsigned int shader = glCreateShader(type);
    glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary, static_cast<GLsizei>(size));
    glSpecializeShader(shader, "main", 0, nullptr, nullptr);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        if(info_log)
            delete[] info_log;
        
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        info_log = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, info_log);

        glDeleteShader(shader);
        return false;
    }

    glAttachShader(program, shader);
    glLinkProgram(program);

    glDeleteShader(shader);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        if(info_log)
            delete[] info_log;
        
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        info_log = new char[length];
        glGetProgramInfoLog(program, length, nullptr, info_log);

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
} // namespace gfx
