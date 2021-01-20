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

    // The window must be literally the first thing created
    // and the last thing destroyed, thus we would need to have
    // a pocket destructor to specifically destroy the GLFW window
    // and shut down the library.
    // And due to this "rule" everything that somewhat related to
    // the GL wrappers should be initialized/used/destroyed inside
    // a brand new scope (go back to main.cc and see the braces).
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

    static void gl_debug_callback(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length, const char *msg, const void *gay)
    {
        logger::log("gl: %s", msg);
    }

    bool init()
    {
        glfwSetErrorCallback(glfw_error);
        if(glfwInit() != GLFW_TRUE) {
            glfwTerminate();
            return false;
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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

        if(!GLAD_GL_VERSION_4_6) {
            logger::log("gl: OpenGL 4.6 is required!");
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }

        glfwSwapInterval(1);

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_debug_callback, nullptr);

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
        globals::current_time = (float)glfwGetTime();
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
