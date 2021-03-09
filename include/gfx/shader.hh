/*
 * shader.hh
 * Created: 2021-03-01, 20:47:32.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

#include <glad/glad.h>

namespace gfx
{
enum class ShaderStage {
    VERTEX,
    FRAGMENT
};

template<ShaderStage T>
constexpr GLenum SHADER_STAGE = 0;
template<>
constexpr GLenum SHADER_STAGE<ShaderStage::VERTEX> = GL_VERTEX_SHADER;
template<>
constexpr GLenum SHADER_STAGE<ShaderStage::FRAGMENT> = GL_FRAGMENT_SHADER;

template<ShaderStage T>
class Shader {
public:
    Shader();
    Shader(Shader &&rhs);
    Shader(const Shader &rhs) = delete;

    virtual ~Shader();

    Shader &operator=(Shader &&rhs);
    Shader &operator=(const Shader &rhs) = delete;

    bool link(const void *binary, size_t size);

    constexpr const char *getInfoLog() const;
    constexpr GLuint get() const;

private:
    char *info_log;
    GLuint program;
};

using VertexShader = Shader<ShaderStage::VERTEX>;
using FragmentShader = Shader<ShaderStage::FRAGMENT>;

template<ShaderStage T>
inline Shader<T>::Shader()
{
    info_log = nullptr;
    program = glCreateProgram();
    glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
}

template<ShaderStage T>
inline Shader<T>::Shader(Shader &&rhs)
{
    info_log = rhs.info_log;
    program = rhs.program;
    rhs.info_log = nullptr;
    rhs.program = 0;
}

template<ShaderStage T>
inline Shader<T>::~Shader()
{
    if(info_log)
        delete[] info_log;
    glDeleteProgram(program);
}

template<ShaderStage T>
inline Shader<T> &Shader<T>::operator=(Shader &&rhs)
{
    Shader copy(std::move(rhs));
    std::swap(copy.info_log, info_log);
    std::swap(copy.program, program);
    return *this;
}

template<ShaderStage T>
inline bool Shader<T>::link(const void *binary, size_t size)
{
    int status;

    if(info_log) {
        delete[] info_log;
        info_log = nullptr;
    }

    unsigned int shader = glCreateShader(SHADER_STAGE<T>);
    glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary, static_cast<GLsizei>(size));
    glSpecializeShader(shader, "main", 0, nullptr, nullptr);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
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
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        info_log = new char[length];
        glGetProgramInfoLog(program, length, nullptr, info_log);

        return false;
    }

    return true;
}

template<ShaderStage T>
inline constexpr const char *Shader<T>::getInfoLog() const
{
    return info_log;
}

template<ShaderStage T>
inline constexpr GLuint Shader<T>::get() const
{
    return program;
}
} // namespace gfx
