/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/client/gl/program.hh>
#include <voxelius/client/gl/texture.hh>
#include <voxelius/client/renderer.hh>
#include <voxelius/client/resources.hh>
#include <voxelius/client/window.hh>
#include <voxelius/cmdline.hh>
#include <voxelius/globals.hh>
#include <voxelius/logger.hh>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char **argv)
{
    cmdline::init(argc, argv);

    if(!window::init())
        return 1;

    {
        Mesh mesh;

        mesh.add_vertex(vertex { vec3_t(-0.75, -0.75, 0.00), vec2_t(0.0, 0.0) });
        mesh.add_vertex(vertex { vec3_t(-0.75,  0.75, 0.00), vec2_t(0.0, 1.0) });
        mesh.add_vertex(vertex { vec3_t( 0.75,  0.75, 0.00), vec2_t(1.0, 1.0) });
        mesh.add_vertex(vertex { vec3_t( 0.75, -0.75, 0.00), vec2_t(1.0, 0.0) });

        mesh.add_index(0);
        mesh.add_index(1);
        mesh.add_index(2);
        mesh.add_index(0);
        mesh.add_index(2);
        mesh.add_index(3);

        mesh.update();

        gl::Program *prog = resources::acquire<gl::Program>("sandbox");
        if(!prog)
            return 1;

        gl::Texture *texture = resources::acquire<gl::Texture>("bgrid.png");
        if(!texture)
            return 1;

        mat4x4_t model = mat4x4_t(1.0);

        int width, height;
        window::get_size(width, height);

        renderer::set_fov(90.0);
        renderer::setup_view(width, height, 0.01, 100.0);
        
        renderer::use_3d_view(vec3_t(0.0, 0.0, -1.0), quat_t());

        renderer::clear_color(vec3_t(0.0, 0.0, 0.1));

        while(window::is_open()) {
            window::begin_frame();

            model = glm::rotate<float>(model, globals::frame_time * 0.25f, vec3_t(0.25, 1.0, 0.5));

            renderer::clear(true, true, false);
            renderer::bind_texture(texture, 0);
            renderer::render(mesh, model, prog);

            window::end_frame();
        }

        resources::release(texture);
        resources::release(prog);
    }
    
    resources::cleanup(true);

    return 0;
}
