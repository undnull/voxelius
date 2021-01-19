/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>
#include <voxelius/gl/vao.hh>
#include <voxelius/util/file.hh>
#include <voxelius/globals.hh>
#include <voxelius/logger.hh>
#include <voxelius/window.hh>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>
#include <stdlib.h>
#include <random>

int main(void)
{
    if(!window::init())
        return 1;

    // Everything related to OpenGL wrappers should
    // be created INSIDE this context so we safely
    // release everything before destroying the window
    // with the context using the AD (see window.cc) class.
    {
        std::vector<uint8_t> vert_bin = util::file_read_bin("./shaders/sandbox.vert.spv");
        std::vector<uint8_t> frag_bin = util::file_read_bin("./shaders/sandbox.frag.spv");

        gl::VertexShader vert;
        gl::FragmentShader frag;
        gl::Program prog;

        gl::Buffer vbo, vbo_uv, ebo;
        gl::VAO vao;

        std::mt19937_64 mtgen((unsigned long long)time(nullptr));
        const size_t nb = 512 * 512;
        uint32_t *pixels = new uint32_t[nb];
        for(size_t i = 0; i < nb; i++) {
            pixels[i] = (mtgen() >> 16) & 0xFFFFFFFF;
        }

        gl::Texture texture;
        texture.load_rgba<uint8_t>(512, 512, pixels);
        texture.set_filter(true);

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

        vec3_t vertices[4] = {
            vec3_t(-1.0, -1.0, 0.0),
            vec3_t(-1.0,  1.0, 0.0),
            vec3_t( 1.0,  1.0, 0.0),
            vec3_t( 1.0, -1.0, 0.0),
        };

        vec2_t texcoords[4] = {
            vec2_t(0.0, 0.0),
            vec2_t(0.0, 1.0),
            vec2_t(1.0, 1.0),
            vec2_t(0.0, 1.0),
        };

        unsigned int indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        vbo.set_data(vertices, sizeof(vertices));
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

        mat4x4_t model = mat4x4_t(1.0);

        while(window::is_open()) {
            window::begin_frame();

            model = glm::rotate(model, (float)globals::frame_time * 0.5f, vec3_t(0.0, 1.0, 0.0));

            glClear(GL_COLOR_BUFFER_BIT);

            prog.bind();
            prog.set_uniform(0, model);
            texture.bind(0);
            vao.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            
            window::end_frame();
        }

        delete[] pixels;
    }

    return 0;
}
