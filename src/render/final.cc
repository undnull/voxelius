/*
 * final.cc
 * Created: 2021-03-03, 13:42:46.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <render/final.hh>
#include <util/fs.hh>
#include <logger.hh>

namespace render
{
struct vertex final {
    float2_t position;
    float2_t texcoord;
};

static const vertex quad_vertices[] = {
    { { -1.0f, -1.0f }, { 0.0f, 0.0f } },
    { { -1.0f,  1.0f }, { 0.0f, 1.0f } },
    { {  1.0f,  1.0f }, { 1.0f, 1.0f } },
    { {  1.0f, -1.0f }, { 1.0f, 0.0f } }
};

static const unsigned int quad_indices[] = {
    0, 1, 2,
    0, 2, 3
};

FinalRenderer::FinalRenderer(int width, int height)
{
    vbo.resize(sizeof(quad_vertices));
    vbo.write(0, quad_vertices, sizeof(quad_vertices));

    ebo.resize(sizeof(quad_indices));
    ebo.write(0, quad_indices, sizeof(quad_indices));

    vao.bindVertexBuffer(vbo, 0, offsetof(vertex, position), sizeof(vertex));
    vao.bindVertexBuffer(vbo, 1, offsetof(vertex, texcoord), sizeof(vertex));
    vao.bindElementBuffer(ebo);

    vao.enableAttribute(0);
    vao.enableAttribute(1);

    vao.setAttributeFormat<float>(0, 2, false);
    vao.setAttributeFormat<float>(1, 2, false);

    vao.setAttributeBinding(0, 0);
    vao.setAttributeBinding(1, 1);

    color.resize(width, height, GL_RGB16F);
    color.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    color.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    color.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    color.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    fbo.attach(GL_COLOR_ATTACHMENT0, color, 0);

    std::vector<uint8_t> vspv = util::readBinaryFile("./shaders/final.vert.spv");
    std::vector<uint8_t> fspv = util::readBinaryFile("./shaders/final.frag.spv");

    if(!vs.link(vspv.data(), vspv.size()))
        logger::log(vs.getInfoLog());
    if(!fs.link(fspv.data(), fspv.size()))
        logger::log(fs.getInfoLog());
    
    pipeline.stage(vs);
    pipeline.stage(fs);
}

void FinalRenderer::render()
{
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindProgramPipeline(pipeline.get());
    glBindTextureUnit(0, color.get());
    glBindVertexArray(vao.get());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
} // namespace render
