/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>
#include <voxelius/gl/vao.hh>
#include <voxelius/globals.hh>
#include <voxelius/logger.hh>
#include <voxelius/resources.hh>
#include <voxelius/window.hh>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

int main(void)
{
    if(!window::init())
        return 1;

    resources::init();

    // Everything related to OpenGL wrappers should
    // be created INSIDE this scope so we safely
    // release everything before destroying the window
    // with the context using the AD (see window.cc) class.
    {
        const vec3_t positions[4] = {
            vec3_t(-0.75, -0.75, 0.00),
            vec3_t(-0.75,  0.75, 0.00),
            vec3_t( 0.75,  0.75, 0.00),
            vec3_t( 0.75, -0.75, 0.00),
        };

        const vec2_t texcoords[4] = {
            vec2_t(0.0, 0.0),
            vec2_t(0.0, 1.0),
            vec2_t(1.0, 1.0),
            vec2_t(1.0, 0.0),
        };

        const unsigned int indices[6] = {
            0, 1, 2,
            0, 2, 3,
        };

        gl::Buffer vbo, vbo_uv;
        gl::Buffer ebo;
        gl::VAO vao;

        vbo.set_data(positions, sizeof(positions));
        vao.bind_vbo(vbo, 0, 0, sizeof(vec3_t));
        vao.enable_attrib(0);
        vao.set_attrib_format<float>(0, 3, false);
        vao.set_attrib_binding(0, 0);

        vbo_uv.set_data(texcoords, sizeof(texcoords));
        vao.bind_vbo(vbo_uv, 1, 0, sizeof(vec2_t));
        vao.enable_attrib(1);
        vao.set_attrib_format<float>(1, 2, false);
        vao.set_attrib_binding(1, 1);

        ebo.set_data(indices, sizeof(indices));
        vao.bind_ebo(ebo);
    
        std::shared_ptr<gl::Program> prog = resources::get_resource<gl::Program>("sandbox");
        if(!prog)
            return 1;

        std::shared_ptr<gl::Texture> texture = resources::get_resource<gl::Texture>("bgrid.png");
        if(!texture)
            return 1;
        
        mat4x4_t model = mat4x4_t(1.0);

        while(window::is_open()) {
            window::begin_frame();

            model = glm::rotate<float>(model, globals::frame_time * 0.25f, vec3_t(0.25, 1.0, 0.5));

            glClear(GL_COLOR_BUFFER_BIT);

            prog->bind();
            prog->set_uniform(0, model);
            texture->bind(0);
            vao.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            window::end_frame();
        }
    }
    
    resources::cleanup();

    return 0;
}
