/*
 * client.cc
 * Created: 2021-01-30, 20:43:38
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/client/gl/program.hh>
#include <voxelius/client/gl/texture.hh>
#include <voxelius/client/client.hh>
#include <voxelius/client/renderer.hh>
#include <voxelius/client/resources.hh>
#include <voxelius/client/window.hh>
#include <voxelius/globals.hh>
#include <glm/gtc/matrix_transform.hpp>

namespace client
{
    bool init()
    {
        if(!window::init())
            return false;
        return true;
    }

    int run()
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

        gl::Program *program = resources::acquire<gl::Program>("sandbox");
        if(!program)
            return 1;
        
        gl::Texture *texture = resources::acquire<gl::Texture>("bgrid.png");
        if(!texture)
            return 1;
        
        mat4x4_t model = mat4x4_t(1.0);

        int width, height;
        window::get_size(width, height);

        renderer::setup_view(width, height, 0.01, 100.0);
        renderer::set_fov(90.0);

        renderer::use_3d_view(vec3_t(0.0, 0.0, -1.0), quat_t());

        renderer::clear_color(vec3_t(0.0, 0.0, 0.25));

        while(window::is_open()) {
            window::begin_frame();

            model = glm::rotate<float>(model, globals::frame_time * 0.25, vec3_t(0.25, 1.0, 0.5));

            renderer::clear(true, true, false);

            renderer::set_program(program);

            renderer::set_texture(texture, 0);
            renderer::render(mesh, model);

            window::end_frame();
        }

        resources::cleanup(true);
        return 0;
    }
}
