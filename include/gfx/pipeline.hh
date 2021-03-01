/*
 * pipeline.hh
 * Created: 2021-03-01, 20:54:37.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gfx/shader.hh>

namespace gfx
{
class Pipeline final {
public:
    Pipeline();
    Pipeline(Pipeline &&rhs);
    Pipeline(const Pipeline &rhs) = delete;

    ~Pipeline();

    Pipeline &operator=(Pipeline &&rhs);
    Pipeline &operator=(const Pipeline &rhs) = delete;

    void setStage(VertexShader &vs);
    void setStage(FragmentShader &fs);

    inline constexpr unsigned int get() const
    {
        return pipeline;
    }

private:
    unsigned int pipeline;
};
} // namespace gfx
