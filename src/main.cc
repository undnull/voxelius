/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <util/commandline.hh>
#include <gfx/pipeline.hh>
#include <gfx/texture.hh>
#include <gfx/vertexarray.hh>
#include <util/logger.hh>
#include <util/clock.hh>
#include <util/fs.hh>
#include <render/final.hh>

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

struct alignas(16) ubo_data_0 final {
    float4x4_t model;
    float4x4_t view;
    float4x4_t projection;
};

struct vertex final {
    float3_t position;
    float2_t uv;
};

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

    int width, height, comp;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *image = stbi_load("./textures/bruh.jpg", &width, &height, &comp, STBI_rgb_alpha);
    if(!image) {
        util::log(stbi_failure_reason());
        glfwTerminate();
        return 1;
    }

    gfx::Texture texture;
    texture.resize(width, height, GL_RGBA16F);
    texture.write(width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
    texture.setParameter(GL_TEXTURE_MAX_ANISOTROPY, 2.0f);
    texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(image);

    std::vector<uint8_t> vspv = util::readBinaryFile("./shaders/sandbox.vert.spv");
    std::vector<uint8_t> fspv = util::readBinaryFile("./shaders/sandbox.frag.spv");

    gfx::VertexShader vs;
    gfx::FragmentShader fs;

    if(!vs.link(vspv.data(), vspv.size()) || !fs.link(fspv.data(), fspv.size())) {
        glfwTerminate();
        return 1;
    }

    gfx::Pipeline pipeline;
    pipeline.stage(vs);
    pipeline.stage(fs);

    vertex vertices[] = {
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f } },
        { {  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f } },
        { {  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f } }
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    gfx::Buffer vbo;
    vbo.resize(sizeof(vertices));
    vbo.write(0, vertices, sizeof(vertices));

    gfx::Buffer ebo;
    ebo.resize(sizeof(indices));
    ebo.write(0, indices, sizeof(indices));

    gfx::VertexArray vao;
    vao.bindElementBuffer(ebo);
    vao.bindVertexBuffer(vbo, 0, offsetof(vertex, position), sizeof(vertex));
    vao.bindVertexBuffer(vbo, 1, offsetof(vertex, uv), sizeof(vertex));
    vao.enableAttribute(0);
    vao.enableAttribute(1);
    vao.setAttributeFormat<float>(0, 3, false);
    vao.setAttributeFormat<float>(1, 2, false);
    vao.setAttributeBinding(0, 0);
    vao.setAttributeBinding(1, 1);

    ubo_data_0 ubo_0;
    ubo_0.model = float4x4_t(1.0f);
    ubo_0.projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
    ubo_0.view = glm::translate(float4x4_t(1.0f), float3_t(0.0f, 0.0f, -1.0f));

    gfx::Buffer ubo;
    ubo.resize(sizeof(ubo_data_0));
    ubo.write(0, &ubo_0, sizeof(ubo_0));

    util::Clock frametime_clock;
    util::Clock print_clock;

    float avg_frametime = 0.0f;

    render::FinalRenderer fr(800, 600);

    while(!glfwWindowShouldClose(window)) {
        float frametime = frametime_clock.reset();
        avg_frametime += frametime;
        avg_frametime /= 2.0f;

        if(print_clock.getTime() >= 1.0f) {
            util::log("FPS: %03.02f dt: %.08f", 1.0f / avg_frametime, avg_frametime);
            print_clock.reset();
        }

        ubo_0.model = glm::rotate(ubo_0.model, frametime * glm::radians(45.0f), float3_t(0.0f, 0.0f, 1.0f));
        ubo.write(offsetof(ubo_data_0, model), &ubo_0.model, sizeof(ubo_0.model));

        glBindFramebuffer(GL_FRAMEBUFFER, fr.getFramebuffer().get());

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(0);
        glBindProgramPipeline(pipeline.get());

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo.get());
        glBindVertexArray(vao.get());
        glBindTextureUnit(0, texture.get());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        fr.render();

        glBindProgramPipeline(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
