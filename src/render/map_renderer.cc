/*
 * map_renderer.cc
 * Created: 2021-03-05, 14:27:35.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/ubo.hh>
#include <render/map_renderer.hh>

namespace render
{
MapRenderer::MapRenderer(int width, int height)
{
    data::ubo_transform t;
    t.projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    transform.resize(sizeof(data::ubo_transform));
    transform.write(0, &t, sizeof(data::ubo_transform));
}

void MapRenderer::setView(const float4x4_t &view)
{
    transform.write(offsetof(data::ubo_transform, view), &view, sizeof(view));
}

void MapRenderer::render(const data::Map &map)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, transform.get());
    
    const auto &layers = map.getLayers();
    for(const auto &layer : layers) {
        glBindProgramPipeline(layer.pipeline.get());
        for(const auto &texture : layer.textures)
            glBindTextureUnit(texture.first, texture.second.get());
        glBindVertexArray(layer.geometry_vao.get());
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(layer.geometry_count), GL_UNSIGNED_INT, nullptr);
    }
}
} // namespace render
