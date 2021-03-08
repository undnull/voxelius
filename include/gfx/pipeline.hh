/*
 * pipeline.hh
 * Created: 2021-03-01, 20:54:37.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gfx/shader.hh>

namespace gfx
{
template<ShaderStage T>
constexpr GLenum SHADER_STAGE_BIT = 0;
template<>
constexpr GLenum SHADER_STAGE_BIT<ShaderStage::VERTEX> = GL_VERTEX_SHADER_BIT;
template<>
constexpr GLenum SHADER_STAGE_BIT<ShaderStage::FRAGMENT> = GL_FRAGMENT_SHADER_BIT;

class Pipeline final {
public:
    Pipeline();
    Pipeline(Pipeline &&rhs);
    Pipeline(const Pipeline &rhs) = delete;

    ~Pipeline();

    Pipeline &operator=(Pipeline &&rhs);
    Pipeline &operator=(const Pipeline &rhs) = delete;

    template<ShaderStage T>
    void stage(const Shader<T> &shader);

    constexpr GLuint get() const;

private:
    GLuint pipeline;
};

inline Pipeline::Pipeline()
{
    glCreateProgramPipelines(1, &pipeline);
}

inline Pipeline::Pipeline(Pipeline &&rhs)
{
    pipeline = rhs.pipeline;
    rhs.pipeline = 0;
}

inline Pipeline::~Pipeline()
{
    glDeleteProgramPipelines(1, &pipeline);
}

inline Pipeline &Pipeline::operator=(Pipeline &&rhs)
{
    Pipeline copy(std::move(rhs));
    std::swap(copy.pipeline, pipeline);
    return *this;
}

template<ShaderStage T>
inline void Pipeline::stage(const Shader<T> &shader)
{
    glUseProgramStages(pipeline, SHADER_STAGE_BIT<T>, shader.get());
}

inline constexpr GLuint Pipeline::get() const
{
    return pipeline;
}
} // namespace gfx
