/*
 * shader.hh
 * Created: 2021-01-19, 10:51:22.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gl/object.hh>
#include <types.hh>

namespace gl
{
class Shader : public Object {
public:
    Shader(unsigned int type);
    virtual ~Shader();

    void create() override;
    void release() override;
    bool isGood() const override;

    void setBinary(const void *binary, size_t size);
    bool specialize(const char *entry);

    inline constexpr unsigned int getType() const
    {
        return type;
    }

    inline constexpr unsigned int getShader() const
    {
        return shader;
    }

    inline constexpr const char *get_info_log() const
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
} // namespace gl
