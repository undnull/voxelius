/*
 * shader.hh
 * Created: 2021-03-01, 20:47:32.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace gfx
{
class Shader {
public:
    Shader(unsigned int type);
    Shader(Shader &&rhs);
    Shader(const Shader &rhs) = delete;

    virtual ~Shader();

    Shader &operator=(Shader &&rhs);
    Shader &operator=(const Shader &rhs) = delete;

    bool link(const void *binary, size_t size);

    inline constexpr unsigned int get() const
    {
        return program;
    }

    inline constexpr const char *getInfoLog() const
    {
        return info_log;
    }

private:
    unsigned int type;
    unsigned int program;
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
} // namespace gfx
