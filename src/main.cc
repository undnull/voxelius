/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>
#include <voxelius/render/mesh.hh>
#include <voxelius/util/file.hh>
#include <voxelius/util/image.hh>
#include <voxelius/globals.hh>
#include <voxelius/logger.hh>
#include <voxelius/window.hh>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

int main(void)
{
    if(!window::init())
        return 1;

    // Everything related to OpenGL wrappers should
    // be created INSIDE this scope so we safely
    // release everything before destroying the window
    // with the context using the AD (see window.cc) class.
    {
        std::vector<uint8_t> vert_bin = util::file_read_bin("./shaders/sandbox.vspv");
        std::vector<uint8_t> frag_bin = util::file_read_bin("./shaders/sandbox.fspv");

        gl::VertexShader vert;
        gl::FragmentShader frag;
        gl::Program prog;

        util::Image img;
        if(!img.load("./textures/bgrid.png")) {
            logger::log("%s", img.get_error());
            return 1;
        }

        gl::Texture texture;
        texture.load_rgba<uint8_t>(img.get_width(), img.get_height(), img.get_pixels());
        texture.set_filter(false);

        vert.set_binary(vert_bin.data(), vert_bin.size());
        if(!vert.specialize("main")) {
            logger::log("%s", vert.get_info_log());
            return 1;
        }

        frag.set_binary(frag_bin.data(), frag_bin.size());
        if(!frag.specialize("main")) {
            logger::log("%s", frag.get_info_log());
            return 1;
        }

        prog.attach(vert);
        prog.attach(frag);
        if(!prog.link()) {
            logger::log("%s", prog.get_info_log());
            return 1;
        }

        frag.release();
        vert.release();

        Mesh mesh;

        mesh.add_vertex(vertex { vec3_t(-0.75, -0.75, 0.0), vec2_t(0.0, 0.0) });
        mesh.add_vertex(vertex { vec3_t(-0.75,  0.75, 0.0), vec2_t(0.0, 1.0) });
        mesh.add_vertex(vertex { vec3_t( 0.75,  0.75, 0.0), vec2_t(1.0, 1.0) });
        mesh.add_vertex(vertex { vec3_t( 0.75, -0.75, 0.0), vec2_t(1.0, 0.0) });

        mesh.add_index(0);
        mesh.add_index(1);
        mesh.add_index(2);
        mesh.add_index(0);
        mesh.add_index(2);
        mesh.add_index(3);

        mesh.update();

        mat4x4_t model = mat4x4_t(1.0);

        while(window::is_open()) {
            window::begin_frame();

            model = glm::rotate(model, (float)globals::frame_time * 0.5f, vec3_t(0.5, 1.0, 0.25));

            glClear(GL_COLOR_BUFFER_BIT);

            prog.bind();
            prog.set_uniform(0, model);
            texture.bind(0);
            mesh.vao.bind();
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh.get_num_indices(), GL_UNSIGNED_INT, nullptr);
            
            window::end_frame();
        }
    }

    return 0;
}
