/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <commandline.hh>
#include <gfx/pipeline.hh>
#include <gfx/vertexarray.hh>
#include <logger.hh>
#include <util/fs.hh>

// clang-format off
// glad should be included first
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

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

struct mt final {
    mat4x4_t model;
    vec4_t color;
};

int main(int argc, char **argv)
{
    CommandLine cl(argc, argv);

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

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    std::vector<uint8_t> vspv = util::readBinaryFile("./shaders/sandbox.vert.spv");
    std::vector<uint8_t> fspv = util::readBinaryFile("./shaders/sandbox.frag.spv");

    gfx::VertexShader vs;
    gfx::FragmentShader fs;

    if(!vs.link(vspv.data(), vspv.size()) || !fs.link(fspv.data(), fspv.size())) {
        glfwTerminate();
        return 1;
    }

    gfx::Pipeline pipeline;
    pipeline.setStage(vs);
    pipeline.setStage(fs);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    gfx::Buffer vbo;
    vbo.resize(sizeof(vertices));
    vbo.write(0, vertices, sizeof(vertices));

    gfx::VertexArray vao;
    vao.bindVertexBuffer(vbo, 0, 0, sizeof(float) * 3);
    vao.enableAttribute(0);
    vao.setAttributeFormat<float>(0, 3, false);
    vao.setAttributeBinding(0, 0);

    mt mubo;
    mubo.model = glm::rotate(mat4x4_t(1.0f), 45.0f, vec3_t(0.0, 0.0, 1.0));
    mubo.color = { 1.0, 0.0, 1.0, 1.0 };

    gfx::Buffer ubo;
    ubo.resize(sizeof(mubo));
    ubo.write(0, &mubo, sizeof(mubo));

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo.get());
    glBindProgramPipeline(pipeline.get());
    glBindVertexArray(vao.get());

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
