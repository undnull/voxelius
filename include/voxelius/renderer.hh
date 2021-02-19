/*
 * renderer.hh
 * Created: 2021-01-22, 23:06:41.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RENDERER_HH
#define VOXELIUS_RENDERER_HH 1
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>
#include <voxelius/gl/vao.hh>

#include <vector>

struct vertex final {
    vec3_t position = vec3_t(0.0, 0.0, 0.0);
    vec2_t texcoord = vec2_t(0.0, 0.0);
};

class Mesh final {
public:
    void clear();

    void addVertex(const vertex &vertex);
    void addIndex(unsigned int index);

    void update();

    inline const size_t getNumVertices() const
    {
        return vertices.size();
    }

    inline const size_t getNumIndices() const
    {
        return indices.size();
    }

public:
    gl::VAO vao;

private:
    gl::Buffer vbo, ebo;
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
};

namespace renderer
{
void setupView(int width, int height, float z_near, float z_far);
void use2dView(const vec3_t &cam_position, const quat_t &cam_rotation);
void use3dView(const vec3_t &cam_position, const quat_t &cam_rotation);

void setFOV(float fov);
float getFOV();

void clearColor(const vec3_t &color);
void clearColor(const vec4_t &color);
void clear(bool color, bool depth, bool stencil);

void setProgram(const gl::Program *program);
void setTexture(const gl::Texture *texture, unsigned int unit);

void render(const Mesh &mesh, const mat4x4_t &model);
} // namespace renderer

#endif
