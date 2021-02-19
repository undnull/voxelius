/*
 * renderer.hh
 * Created: 2021-01-22, 23:06:41.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_CLIENT_RENDERER_HH
#define VOXELIUS_CLIENT_RENDERER_HH 1
#include <voxelius/client/gl/program.hh>
#include <voxelius/client/gl/texture.hh>
#include <voxelius/client/gl/vao.hh>

#include <vector>

struct vertex final {
    vec3_t position = vec3_t(0.0, 0.0, 0.0);
    vec2_t texcoord = vec2_t(0.0, 0.0);
};

class Mesh final {
public:
    void clear();

    void add_vertex(const vertex &vertex);
    void add_index(unsigned int index);

    void update();

    inline const size_t get_num_vertices() const
    {
        return vertices.size();
    }

    inline const size_t get_num_indices() const
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
void setup_view(int width, int height, float z_near, float z_far);
void use_2d_view(const vec3_t &cam_position, const quat_t &cam_rotation);
void use_3d_view(const vec3_t &cam_position, const quat_t &cam_rotation);

void set_fov(float fov);
float get_fov();

void clear_color(const vec3_t &color);
void clear_color(const vec4_t &color);
void clear(bool color, bool depth, bool stencil);

void set_program(const gl::Program *program);
void set_texture(const gl::Texture *texture, unsigned int unit);

void render(const Mesh &mesh, const mat4x4_t &model);
} // namespace renderer

#endif
