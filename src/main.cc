/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <editor/editor.hh>
#include <util/logger.hh>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
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
    util::CommandLine args(argc, argv);

    if(!glfwInit())
        return 1;

    int width = 800;
    int height = 600;
    GLFWmonitor *monitor = nullptr;

    if(args.hasArgument("--width"))
        width = atoi(args.getArgument("--width"));
    if(args.hasArgument("--height"))
        height = atoi(args.getArgument("--height"));
    if(args.hasOption("--fullscreen"))
        monitor = glfwGetPrimaryMonitor();

    if(args.hasOption("--native")) {
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        width = mode->width;
        height = mode->height;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(width, height, "Voxelius", monitor, nullptr);
    if(!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGL()) {
        glfwTerminate();
        return 1;
    }

    if(!GLAD_GL_VERSION_4_6) {
        util::log("opengl: version 4.6 is required (while %d.%d is present)", GLVersion.major, GLVersion.minor);
        glfwTerminate();
        return false;
    }

    glfwSwapInterval(1);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    const unsigned int nvidia_131185 = 131185;
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, &nvidia_131185, GL_FALSE);

    if(args.hasOption("--editor")) {
        util::log("starting editor");
        int code = editor::run(args, window);
        glfwDestroyWindow(window);
        glfwTerminate();
        return code;
    }

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
