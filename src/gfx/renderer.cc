/*
 * renderer.cc
 * Created: 2021-01-22, 23:16:03.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gfx/renderer.hh>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stack>

namespace gfx::renderer
{
    static std::stack<view> view_stack;

    static inline const mat4x4_t get_view()
    {
        if(view_stack.empty())
            return mat4x4_t(1.0);
        return view_stack.top().matrix;
    }

    void push_2d_view(int width, int height, int top, int left, float z_near, float z_far)
    {
        view view;
        view.top = top;
        view.left = left;
        view.width = width;
        view.height = height;
        view.z_near = z_near;
        view.z_far = z_far;
        view.matrix = glm::ortho<float>(view.left, view.width, view.height, view.top, view.z_near, view.z_far);
        view_stack.push(view);
    }

    void push_3d_view(int width, int height, float fov, float z_near, float z_far)
    {
        view view;
        view.width = width;
        view.height = height;
        view.aspect = (float)view.width / (float)view.height;
        view.fov = fov;
        view.z_near = z_near;
        view.z_far = z_far;
        view.matrix = glm::perspective<float>(view.fov, view.aspect, view.z_near, view.z_far);
        view_stack.push(view);
    }

    void pop_view()
    {
        if(view_stack.empty())
            return;
        view_stack.pop();
    }

    void bind_texture(const gl::Texture *texture, unsigned int unit)
    {
        glBindTextureUnit(unit, texture ? texture->get_texture() : 0);
    }

    void render(const Mesh &mesh, const mat4x4_t &mm, const gl::Program *program)
    {
        if(program) {
            glUseProgram(program->get_program());
            program->set_uniform(0, get_view());
            program->set_uniform(1, mm);
        }

        glBindVertexArray(mesh.vao.get_vao());
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh.get_num_indices(), GL_UNSIGNED_INT, nullptr);
    }
}
