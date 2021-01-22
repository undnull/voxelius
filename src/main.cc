/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gfx/renderer.hh>
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>
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

    {
        gfx::Mesh mesh;

        mesh.add_vertex(gfx::vertex { vec3_t(-0.75, -0.75, 0.00), vec2_t(0.0, 0.0) });
        mesh.add_vertex(gfx::vertex { vec3_t(-0.75,  0.75, 0.00), vec2_t(0.0, 1.0) });
        mesh.add_vertex(gfx::vertex { vec3_t( 0.75,  0.75, 0.00), vec2_t(1.0, 1.0) });
        mesh.add_vertex(gfx::vertex { vec3_t( 0.75, -0.75, 0.00), vec2_t(1.0, 0.0) });

        mesh.add_index(0);
        mesh.add_index(1);
        mesh.add_index(2);
        mesh.add_index(0);
        mesh.add_index(2);
        mesh.add_index(3);

        mesh.update();

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
            gfx::renderer::bind_texture(texture.get(), 0);
            gfx::renderer::render(mesh, model, prog.get());

            window::end_frame();
        }
    }
    
    resources::release_all();

    return 0;
}
