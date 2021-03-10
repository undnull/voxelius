/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/image.hh>
#include <data/vidmode.hh>
#include <render/sprite_renderer.hh>
#include <ui/logger_out.hh>
#include <ui/menu_bar.hh>
#include <ui/ui.hh>
#include <util/clock.hh>
#include <util/logger.hh>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

inline bool checkGLSuitability()
{
    if(GLAD_GL_VERSION_4_6)
        return true;

    struct gl_extension final {
        const char *id;
        const int present;
    };

    const gl_extension extensions[] = {
        //{ "ARB_texture_filter_anisotropic", GLAD_GL_ARB_texture_filter_anisotropic },
        { "ARB_shader_storage_buffer_object", GLAD_GL_ARB_shader_storage_buffer_object },
        { "ARB_direct_state_access", GLAD_GL_ARB_direct_state_access },
        { "ARB_gl_spirv", GLAD_GL_ARB_gl_spirv },
        { nullptr, 0 }
    };

    const gl_extension *extension = extensions;
    do {
        if(!extension->present) {
            util::log("opengl: extension %s is not present", extension->id);
            return false;
        }
        extension++;
    } while(extension->id && extension->present);

    return true;
}

int main(int argc, char **argv)
{
    util::CommandLine args(argc, argv);

    if(!glfwInit())
        return 1;

    data::VidMode vidmode;
    vidmode.loadFromFile("vidmode.json");
    vidmode.loadFromArgs(args);

    glfwWindowHint(GLFW_SAMPLES, 4);
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

    if(!checkGLSuitability()) {
        glfwTerminate();
        return false;
    }

    glfwSwapInterval(vidmode.swap_interval);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    const unsigned int nvidia_131185 = 131185;
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, &nvidia_131185, GL_FALSE);

    // All the GL-related (objects) stuff should be done
    // inside of this scope to avoid destructor calls when
    // the window is destroyed and the GL context is gone
    {
        // sprite
        struct {
            float2_t size;
            gfx::Texture texture;
            data::Transform transform;
        } sprite;

        data::Image image;
        if(!image.loadFromFile("textures/bruh.jpg"))
            return false;

        int width, height;
        image.getSize(width, height);

        sprite.size = float2_t(100.0f, 100.0f);
        sprite.texture.storage(width, height, GL_RGBA16F);
        sprite.texture.subImage(width, height, data::Image::TEXTURE_FORMAT, data::Image::TEXTURE_TYPE, image.getPixels());
        sprite.texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        sprite.texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        sprite.texture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        sprite.texture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        sprite.transform.setOrigin(float2_t(50.0f, 50.0f));

        std::vector<data::Transform> transforms;

        // Sprite #1
        sprite.transform.setPosition(float2_t(100.0f, 100.0f));
        transforms.push_back(sprite.transform);

        // Sprite #2
        sprite.transform.setPosition(float2_t(250.0f, 100.0f));
        transforms.push_back(sprite.transform);

        // Sprite #3
        sprite.transform.setPosition(float2_t(400.0f, 100.0f));
        transforms.push_back(sprite.transform);

        render::SpriteRenderer sprite_renderer(vidmode.width, vidmode.height);
        sprite_renderer.setView(data::View());

        ui::init(window);
        ui::LoggerOut logger_out;
        ui::MenuBar menu_bar;

        while(!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(0);

            sprite_renderer.draw(transforms, sprite.texture, sprite.size);

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
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    vidmode.saveToFile("vidmode.json");

    return 0;
}
