/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/tileset.hh>
#include <util/fs.hh>
#include <util/commandline.hh>
#include <util/logger.hh>
#include <gfx/pipeline.hh>
#include <gfx/vertexarray.hh>

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

struct vertex final {
    float2_t position;
    float2_t texcoord;
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

    data::TileSet ts;
    if(!ts.load("./tilesets/ts.json"))
        return 1;

    data::tile tile = ts.getTile(0);
    util::log("(%f; %f) to (%f; %f)", tile.top, tile.left, tile.bottom, tile.right);    

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
        { { -0.5f, -0.5f }, { tile.left, tile.bottom } },
        { { -0.5f, 0.5f }, { tile.left, tile.top } },
        { { 0.5f, 0.5f }, { tile.right, tile.top } },
        { { 0.5f, -0.5f }, { tile.right, tile.bottom } }
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
    vao.bindVertexBuffer(vbo, 1, offsetof(vertex, texcoord), sizeof(vertex));
    vao.enableAttribute(0);
    vao.enableAttribute(1);
    vao.setAttributeFormat<float>(0, 2, false);
    vao.setAttributeFormat<float>(1, 2, false);
    vao.setAttributeBinding(0, 0);
    vao.setAttributeBinding(1, 1);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(0);
        glBindProgramPipeline(pipeline.get());

        glBindVertexArray(vao.get());
        glBindTextureUnit(0, ts.getTexture().get());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glBindProgramPipeline(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
