/*
 * window.cc
 * Created: 2021-01-16, 15:42:43.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/cmdline.hh>
#include <voxelius/globals.hh>
#include <voxelius/logger.hh>
#include <voxelius/client/window.hh>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

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

    static void glfw_error_callback(int code, const char *msg)
    {
        logger::log("window: glfw error %d: %s", code, msg);
    }

    static void gl_debug_callback(unsigned int src, unsigned int type, unsigned int id, unsigned int severity, int length, const char *msg, const void *arg)
    {
        switch(severity) {
            case GL_DEBUG_SEVERITY_HIGH:
            case GL_DEBUG_SEVERITY_MEDIUM:
                logger::log("opengl: %s", msg);
                break;
            default:
                logger::dlog("opengl: %s", msg);
                break;
        }
    }

    bool init()
    {
        glfwSetErrorCallback(glfw_error_callback);
        if(glfwInit() != GLFW_TRUE) {
            glfwTerminate();
            return false;
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        const char *argument;
        int width = 640;
        int height = 480;
        bool fullscreen = false;
        bool vsync = true;

        argument = cmdline::get_argument("--width");
        if(argument)
            width = atoi(argument);

        argument = cmdline::get_argument("--height");
        if(argument)
            height = atoi(argument);
        
        if(cmdline::has_option("--fullscreen"))
            fullscreen = true;
        
        if(cmdline::has_option("--vsync"))
            vsync = true;

        GLFWmonitor *monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        window = glfwCreateWindow(width, height, "Voxelius", monitor, nullptr);
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
            logger::log("opengl: opengl version 4.6 is required");
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }

        glfwSwapInterval(vsync ? 1 : 0);

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_debug_callback, nullptr);

        // todo: debug
        glfwSetKeyCallback(window, [](GLFWwindow *w, int key, int, int action, int) {
            if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(w, GLFW_TRUE);
        });

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

    void get_size(int &width, int &height)
    {
        glfwGetWindowSize(window, &width, &height);
    }
}
