/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/program.hh>
#include <voxelius/gl/vao.hh>
#include <voxelius/util/file.hh>
#include <voxelius/logger.hh>
#include <voxelius/window.hh>
#include <glad/glad.h>

int main(void)
{
    if(!window::init())
        return 1;

    // Everything related to OpenGL wrappers should
    // be created INSIDE this context so we safely
    // release everything before destroying the window
    // with the context using the AD (see window.cc) class.
    {
        std::vector<uint8_t> vert_bin = util::file_read_bin("./shaders/triangle.vspv");
        std::vector<uint8_t> frag_bin = util::file_read_bin("./shaders/triangle.fspv");

        gl::VertexShader vert;
        gl::FragmentShader frag;
        gl::Program prog;

        gl::Buffer vbo;
        gl::VAO vao;

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

        vec3_t vertices[3] = {
            vec3_t(-0.5, -0.5, 0.0),
            vec3_t( 0.0,  0.5, 0.0),
            vec3_t( 0.5, -0.5, 0.0),
        };

        vbo.set_data(vertices, sizeof(vertices));
        vao.bind_vbo(vbo, 0, 0, sizeof(vec3_t));
        vao.enable_attrib(0);
        vao.set_attrib_format<float>(0, 3, false);
        vao.set_attrib_binding(0, 0);

        while(window::is_open()) {
            window::begin_frame();

            glClear(GL_COLOR_BUFFER_BIT);

            prog.bind();
            vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            window::end_frame();
        }
    }

    return 0;
}
