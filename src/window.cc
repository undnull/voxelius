/*
 * window.cc
 * Created: 2021-01-16, 15:42:43.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/globals.hh>
#include <voxelius/logger.hh>
#include <voxelius/window.hh>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace window
{
    static GLFWwindow *window;

    static class AD final {
    public:
        ~AD()
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    } ad;

    static void glfw_error(int code, const char *message)
    {
        logger::log("glfw error %d: %s", code, message);
    }

    bool init()
    {
        glfwSetErrorCallback(glfw_error);
        if(glfwInit() != GLFW_TRUE) {
            glfwTerminate();
            return false;
        }

        window = glfwCreateWindow(800, 600, "Voxelius", nullptr, nullptr);
        if(!window) {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        if(!gladLoadGL()) {
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }

        glfwSwapInterval(1);

        return true;
    }

    bool is_open()
    {
        return glfwWindowShouldClose(window) != GLFW_TRUE;
    }

    void close()
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void begin_frame()
    {
        globals::current_time = glfwGetTime();
        globals::frame_time = globals::current_time - globals::last_time;
        globals::last_time = globals::current_time;
    }

    void end_frame()
    {
        glfwSwapBuffers(window);
        if(glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE)
            glfwPollEvents();
        else
            glfwWaitEventsTimeout(0.05);
    }

    GLFWwindow * get_window()
    {
        return window;
    }
}
