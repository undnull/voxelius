/*
 * common.hh
 * Created: 2021-03-08, 18:45:39.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <data/transform.hh>
#include <data/vertex.hh>
#include <data/view.hh>
#include <gfx/framebuffer.hh>
#include <gfx/pipeline.hh>
#include <gfx/vertex_array.hh>
#include <util/fs.hh>
#include <util/logger.hh>

namespace render
{
enum class RenderMode {
    NORMAL,
    POINTS,
    WIREFRAME,
};

template<RenderMode T>
inline constexpr GLenum RENDER_MODE = 0;
template<>
inline constexpr GLenum RENDER_MODE<RenderMode::NORMAL> = GL_LINE;
template<>
inline constexpr GLenum RENDER_MODE<RenderMode::POINTS> = GL_POINT;
template<>
inline constexpr GLenum RENDER_MODE<RenderMode::WIREFRAME> = GL_FILL;

} // namespace render
