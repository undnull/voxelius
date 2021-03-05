/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/map.hh>
#include <util/fs.hh>
#include <util/commandline.hh>
#include <util/logger.hh>
#include <gfx/pipeline.hh>
#include <gfx/vertexarray.hh>
#include <render/maprenderer.hh>

// clang-format off
// glad should be included first
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <stb_image.h>

static void debugCallback(unsigned int src, unsigned int type, unsigned int id, unsigned int severity, int length, const char *msg, const void *arg)
{
    switch(severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        case GL_DEBUG_SEVERITY_MEDIUM:
            util::log("opengl: %s", msg);
            break;
        default:
            util::dlog("opengl: %s", msg);
            break;
    }
}

int main(int argc, char **argv)
{
    util::CommandLine cl(argc, argv);

    if(!glfwInit())
        return 1;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Voxelius", nullptr, nullptr);
    if(!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGL()) {
        glfwTerminate();
        return 1;
    }

    glfwSwapInterval(0);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    data::Map map;
    if(!map.loadFromFile("maps/sandbox.json"))
        return 1;

    render::MapRenderer renderer(800, 600);
    renderer.setView(glm::scale(float4x4_t(1.0f), float3_t(1.5f, 1.5f, 1.0f)));

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(0);

        renderer.render(map);

        glBindProgramPipeline(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
