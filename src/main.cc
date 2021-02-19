/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/cmdline.hh>
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>
#include <voxelius/globals.hh>
#include <voxelius/renderer.hh>
#include <voxelius/resources.hh>
#include <voxelius/window.hh>

#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char **argv)
{
    cmdline::init(argc, argv);

    if(!window::init())
        return 1;

    Mesh mesh;

    mesh.addVertex(vertex { vec3_t(-0.75, -0.75, 0.00), vec2_t(0.0, 0.0) });
    mesh.addVertex(vertex { vec3_t(-0.75, 0.75, 0.00), vec2_t(0.0, 1.0) });
    mesh.addVertex(vertex { vec3_t(0.75, 0.75, 0.00), vec2_t(1.0, 1.0) });
    mesh.addVertex(vertex { vec3_t(0.75, -0.75, 0.00), vec2_t(1.0, 0.0) });

    mesh.addIndex(0);
    mesh.addIndex(1);
    mesh.addIndex(2);
    mesh.addIndex(0);
    mesh.addIndex(2);
    mesh.addIndex(3);

    mesh.update();

    gl::Program *program = resources::acquire<gl::Program>("sandbox");
    if(!program)
        return 1;

    gl::Texture *texture = resources::acquire<gl::Texture>("bgrid.png");
    if(!texture)
        return 1;

    mat4x4_t model = mat4x4_t(1.0);

    int width, height;
    window::getSize(width, height);

    renderer::setupView(width, height, 0.01, 100.0);
    renderer::setFOV(90.0);

    renderer::use3dView(vec3_t(0.0, 0.0, -1.0), quat_t());

    renderer::clearColor(vec3_t(0.0, 0.0, 0.25));

    while(window::isOpen()) {
        window::beginFrame();

        model = glm::rotate<float>(model, globals::frame_time * 0.25, vec3_t(0.25, 1.0, 0.5));

        renderer::clear(true, true, false);

        renderer::setProgram(program);

        renderer::setTexture(texture, 0);
        renderer::render(mesh, model);

        window::endFrame();
    }

    resources::cleanup(true);
    return 0;
}
