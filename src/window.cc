/*
 * window.cc
 * Created: 2021-01-16, 15:42:43.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <globals.hh>
#include <logger.hh>
#include <window.hh>

// clang-format off
// glad must be included first
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <stdlib.h>

static void errorCallback(int code, const char *msg)
{
    logger::log("glfw error %d: %s", code, msg);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    static_cast<WindowBase *>(glfwGetWindowUserPointer(window))->onKey(key, scancode, action, mods);
}

static void charCallback(GLFWwindow *window, unsigned int unicode)
{
    static_cast<WindowBase *>(glfwGetWindowUserPointer(window))->onChar(unicode);
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    static_cast<WindowBase *>(glfwGetWindowUserPointer(window))->onMouseButton(button, action, mods);
}

static void cursorPosCallback(GLFWwindow *window, double x, double y)
{
    static_cast<WindowBase *>(glfwGetWindowUserPointer(window))->onCursorPos((float)x, (float)y);
}

static void debugCallback(unsigned int src, unsigned int type, unsigned int id, unsigned int severity, int length, const char *msg, const void *arg)
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

static class AD final {
public:
    ~AD()
    {
        glfwTerminate();
    }

    void init()
    {
        if(!init_called) {
            init_called = true;
            glfwSetErrorCallback(errorCallback);
            glfwInit();
        }
    }

    bool init_called = false;
} ad;

WindowBase::WindowBase(int width, int height, const char *title, bool fullscreen)
{
    ad.init();

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if(window) {
        glfwSetWindowUserPointer(window, this);

        glfwSetKeyCallback(window, keyCallback);
        glfwSetCharCallback(window, charCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, cursorPosCallback);

        glfwMakeContextCurrent(window);

        if(!gladLoadGL()) {
            glfwDestroyWindow(window);
            window = nullptr;
            return;
        }

        if(!GLAD_GL_VERSION_4_6) {
            logger::log("opengl: opengl version 4.6 is required");
            glfwDestroyWindow(window);
            window = nullptr;
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);
    }
}

WindowBase::~WindowBase()
{
    if(window)
        glfwDestroyWindow(window);
}

void WindowBase::setVSyncEnabled(bool b)
{
    glfwSwapInterval(b ? 1 : 0);
}

bool WindowBase::isOpen() const
{
    if(window)
        return glfwWindowShouldClose(window) == GLFW_FALSE;
    return false;
}

void WindowBase::close()
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void WindowBase::endFrame()
{
    if(glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE)
        glfwPollEvents();
    else
        glfwWaitEventsTimeout(0.05);
    glfwSwapBuffers(window);
}

void WindowBase::getSize(int &width, int &height)
{
    glfwGetWindowSize(window, &width, &height);
}

GLFWwindow *WindowBase::getWindow() const
{
    return window;
}

void WindowBase::onKey(int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        close();
}

void WindowBase::onChar(unsigned int unicode)
{
}

void WindowBase::onMouseButton(int button, int action, int mods)
{
}

void WindowBase::onCursorPos(float x, float y)
{
}
