/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/image.hh>
#include <data/vidmode.hh>
#include <input/keyboard.hh>
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

static bool checkGLSuitability()
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

static void errorCallback(int code, const char *message)
{
    util::log("glfw error %d: %s", code, message);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    //ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    input::keyCallback(key, action);
}

int main(int argc, char **argv)
{
    util::CommandLine args(argc, argv);

    glfwSetErrorCallback(errorCallback);
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

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    glfwSetKeyCallback(window, keyCallback);

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

        // Sprite #4
        transforms.push_back(sprite.transform);

        // Sprite #5 = 2, 3 and 4 combined
        transforms.push_back(sprite.transform);

        render::SpriteRenderer sprite_renderer(vidmode.width, vidmode.height);

        data::View view;
        sprite_renderer.setView(view);

        //ui::init(window);
        //ui::LoggerOut logger_out;
        //ui::MenuBar menu_bar;

        util::Clock clock;
        float sincos_angle = 0.0f;

        util::Clock perf;

        while(!glfwWindowShouldClose(window)) {
            const float frametime = clock.reset();

            {
                float2_t velocity = float2_t(0.0f, 0.0f);
                if(input::isKeyPressed(GLFW_KEY_W))
                    velocity.y += 1.0f;
                if(input::isKeyPressed(GLFW_KEY_A))
                    velocity.x += 1.0f;
                if(input::isKeyPressed(GLFW_KEY_S))
                    velocity.y += -1.0f;
                if(input::isKeyPressed(GLFW_KEY_D))
                    velocity.x += -1.0f;
                
                if(glm::abs(glm::length(velocity)) > 0.0f) {
                    view.move(velocity * 128.0f * frametime);
                    sprite_renderer.setView(view);
                }
            }

            if(perf.getTime() >= 1.0f) {
                util::log("momentary frametime: %f (%f FPS)", frametime, 1.0f / frametime);
                perf.reset();
            }

            transforms[0].rotate(90.0f * frametime);
            transforms[1].rotate(90.0f * frametime * cos(sincos_angle));
            transforms[2].setScale(sin(sincos_angle));
            transforms[3].setPosition(float2_t(550.0f, 100.0f) + 42.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));
            //transforms[3].move(50.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));

            transforms[4].rotate(90.0f * frametime * cos(sincos_angle));
            transforms[4].setScale(sin(sincos_angle));
            transforms[4].setPosition(float2_t(250.0f, 350.0f) + 75.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));
            //transforms[4].move(50.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));

            sincos_angle += frametime;

            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(0);

            sprite_renderer.draw(transforms, sprite.texture, sprite.size);

            //const ImGuiIO &io = ui::beginFrame();
            //logger_out.draw(io);
            //menu_bar.draw(io);
            //ui::endFrame();

            //if(menu_bar.file_exit) {
            //    glfwSetWindowShouldClose(window, GLFW_TRUE);
            //    menu_bar.file_exit = false;
            //}

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
