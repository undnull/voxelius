/*
 * program.hh
 * Created: 2021-01-19, 11:34:43.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_CLIENT_GL_PROGRAM_HH
#define VOXELIUS_CLIENT_GL_PROGRAM_HH 1
#include <voxelius/client/gl/shader.hh>

namespace gl
{
class Program final : public Object {
public:
    Program();
    ~Program();

    void create() override;
    void release() override;
    bool isGood() const override;

    void attach(const Shader &shader);
    bool link();

    void setUniform(int location, const int value) const;
    void setUniform(int location, const float value) const;
    void setUniform(int location, const vec2_t &value) const;
    void setUniform(int location, const vec3_t &value) const;
    void setUniform(int location, const vec4_t &value) const;
    void setUniform(int location, const mat4x4_t &value) const;

    inline constexpr unsigned int getProgram() const
    {
        return program;
    }

    inline constexpr const char *getInfoLog() const
    {
        return info_log;
    }

private:
    unsigned int program;
    char *info_log;
};
} // namespace gl

#endif
