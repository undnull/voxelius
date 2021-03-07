/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/vidmode.hh>
#include <ui/logger_out.hh>
#include <ui/menu_bar.hh>
#include <ui/ui.hh>
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

    data::VidMode vidmode;
    vidmode.loadFromFile("vidmode.json");
    vidmode.loadFromArgs(args);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, vidmode.border);
    GLFWwindow *window = glfwCreateWindow(vidmode.width, vidmode.height, "Voxelius", vidmode.monitor, nullptr);
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

    glfwSwapInterval(vidmode.swap_interval);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    const unsigned int nvidia_131185 = 131185;
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, &nvidia_131185, GL_FALSE);

    ui::init(window);
    ui::LoggerOut logger_out;
    ui::MenuBar menu_bar;

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(0);

        const ImGuiIO &io = ui::beginFrame();
        logger_out.draw(io);
        menu_bar.draw(io);
        ui::endFrame();

        if(menu_bar.file_exit) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            menu_bar.file_exit = false;
        }

        glBindProgramPipeline(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    vidmode.saveToFile("vidmode.json");

    return 0;
}
