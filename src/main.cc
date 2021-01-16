/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/buffer.hh>
#include <voxelius/gl/program.hh>
#include <voxelius/gl/vao.hh>
#include <voxelius/window.hh>
#include <glad/glad.h>
#include <iostream>

static const char *vs_src =
    "#version 420\n"
    "layout(location = 0) in vec3 vtx;\n"
    "void main(void)\n"
    "{\n"
    "    gl_Position = vec4(vtx, 1.0);\n"
    "}\n";

static const char *fs_src =
    "#version 420\n"
    "layout(location = 0) out vec4 target;\n"
    "void main(void)\n"
    "{\n"
    "    target = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

int main(void)
{
    if(!window::init())
        return 1;

    gl::VertexShader vs;
    gl::FragmentShader fs;    
    gl::Program prog;
    gl::Buffer vbo(GL_ARRAY_BUFFER);
    gl::Buffer ebo(GL_ELEMENT_ARRAY_BUFFER);
    gl::VAO vao;

    const float3 vertices[3] = {
        float3(-0.5f, -0.5f, 0.0f),
        float3( 0.0f,  0.5f, 0.0f),
        float3( 0.5f, -0.5f, 0.0f),
    };

    const unsigned int indices[3] = { 0, 1, 2 };

    vs.set_source(vs_src);
    if(!vs.try_compile()) {
        std::cerr << vs.get_info_log() << std::endl;
        return 1;
    }

    fs.set_source(fs_src);
    if(!fs.try_compile()) {
        std::cerr << fs.get_info_log() << std::endl;
        return 1;
    }

    prog.attach(vs);
    prog.attach(fs);
    if(!prog.try_link()) {
        std::cerr << prog.get_info_log() << std::endl;
        return 1;
    }

    vao.bind();

    vbo.bind();
    vbo.set_data(vertices, sizeof(vertices));

    ebo.bind();
    ebo.set_data(indices, sizeof(indices));

    vao.enable_attrib(0);
    vao.set_attrib_ptr(0, sizeof(float3), 3, 0);

    vao.unbind();

    while(window::is_open()) {
        window::begin_frame();

        glClear(GL_COLOR_BUFFER_BIT);

        prog.bind();

        vao.bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        window::end_frame();
    }

    return 0;
}
