/*
 * renderer.cc
 * Created: 2021-01-22, 23:16:03.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/renderer.hh>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace renderer
{
    static int view_width = 0;
    static int view_height = 0;
    static float view_aspect = 0.0;
    static float view_fov = 0.0;
    static float view_z_near = 0.0;
    static float view_z_far = 0.0;

    static mat4x4_t view_matrix = mat4x4_t(1.0);

    void setup_view(int width, int height, float z_near, float z_far)
    {
        view_width = width;
        view_height = height;
        view_aspect = (float)width / (float)height;
        view_z_near = z_near;
        view_z_far = z_far;
    }

    void store_view()
    {
        // unimplemented
    }

    void restore_view()
    {
        // unimplemented
    }

    void use_2d_view(const vec3_t &cam_position, const quat_t &cam_rotation)
    {
        view_matrix = glm::ortho<float>(-1.0, 1.0, 1.0 * view_aspect, -1.0 * view_aspect, view_z_near, view_z_far);
        view_matrix = glm::translate(view_matrix, cam_position);
        view_matrix = view_matrix * glm::mat4_cast(cam_rotation);
    }

    void use_3d_view(const vec3_t &cam_position, const quat_t &cam_rotation)
    {
        view_matrix = glm::perspective<float>(glm::radians(view_fov), view_aspect, view_z_near, view_z_far);
        view_matrix = glm::translate(view_matrix, cam_position);
        view_matrix = view_matrix * glm::mat4_cast(cam_rotation);
    }

    void set_fov(float fov)
    {
        view_fov = fov;
    }

    float get_fov()
    {
        return view_fov;
    }

    void clear_color(const vec3_t &color)
    {
        glClearColor(color.r, color.g, color.b, 1.0);
    }

    void clear_color(const vec4_t &color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void clear(bool color, bool depth, bool stencil)
    {
        GLbitfield bits = 0;
        if(color)
            bits |= GL_COLOR_BUFFER_BIT;
        if(depth)
            bits |= GL_DEPTH_BUFFER_BIT;
        if(stencil)
            bits |= GL_STENCIL_BUFFER_BIT;
        glClear(bits);
    }

    // This should be removed as soon as the material system is implemented
    void bind_texture(const gl::Texture *texture, unsigned int unit)
    {
        glBindTextureUnit(unit, texture ? texture->get_texture() : 0);
    }

    void render(const Mesh &mesh, const mat4x4_t &mm, const gl::Program *program)
    {
        if(program) {
            glUseProgram(program->get_program());
            program->set_uniform(0, view_matrix);
            program->set_uniform(1, mm);
        }

        glBindVertexArray(mesh.vao.get_vao());
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh.get_num_indices(), GL_UNSIGNED_INT, nullptr);
    }
}