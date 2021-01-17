/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/buffer.hh>
#include <voxelius/gl/program.hh>
#include <voxelius/gl/vao.hh>
#include <voxelius/render/mesh.hh>
#include <voxelius/util/file.hh>
#include <voxelius/logger.hh>
#include <voxelius/window.hh>
#include <glad/glad.h>

int main(void)
{
    if(!window::init())
        return 1;

    gl::VertexShader vs;
    gl::FragmentShader fs;    
    gl::Program prog;

    render::Mesh mesh;

    mesh.add_vertex(render::vertex { vec3_t(-0.5, -0.5, 0.0) });
    mesh.add_vertex(render::vertex { vec3_t( 0.0,  0.5, 0.0) });
    mesh.add_vertex(render::vertex { vec3_t( 0.5, -0.5, 0.0) });

    mesh.add_index(0);
    mesh.add_index(1);
    mesh.add_index(2);

    mesh.update();

    const std::string vs_src = util::file_read_txt("./shaders/triangle.vs");
    const std::string fs_src = util::file_read_txt("./shaders/triangle.fs");

    vs.set_source(vs_src.c_str());
    if(!vs.try_compile()) {
        logger::log("%s", vs.get_info_log());
        return 1;
    }

    fs.set_source(fs_src.c_str());
    if(!fs.try_compile()) {
        logger::log("%s", fs.get_info_log());
        return 1;
    }

    prog.attach(vs);
    prog.attach(fs);
    if(!prog.try_link()) {
        logger::log("%s", prog.get_info_log());
        return 1;
    }

    while(window::is_open()) {
        window::begin_frame();

        glClear(GL_COLOR_BUFFER_BIT);

        prog.bind();

        mesh.get_vao().bind();
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh.get_num_indices(), GL_UNSIGNED_INT, nullptr);

        window::end_frame();
    }

    return 0;
}
