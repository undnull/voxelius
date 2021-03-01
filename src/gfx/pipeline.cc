/*
 * pipeline.cc
 * Created: 2021-03-01, 20:58:01.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <gfx/pipeline.hh>

#include <glad/glad.h>

#include <utility>

namespace gfx
{
Pipeline::Pipeline()
{
    glCreateProgramPipelines(1, &pipeline);
}

Pipeline::Pipeline(Pipeline &&rhs)
{
    pipeline = rhs.pipeline;
    rhs.pipeline = 0;
}

Pipeline::~Pipeline()
{
    glDeleteProgramPipelines(1, &pipeline);
}

Pipeline &Pipeline::operator=(Pipeline &&rhs)
{
    Pipeline copy(std::move(rhs));
    std::swap(copy.pipeline, pipeline);
    return *this;
}

void Pipeline::setStage(VertexShader &vs)
{
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vs.get());
}

void Pipeline::setStage(FragmentShader &fs)
{
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fs.get());
}
} // namespace gfx
