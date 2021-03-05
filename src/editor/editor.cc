/*
 * editor.cc
 * Created: 2021-03-05, 19:38:48.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <editor/editor.hh>
#include <data/map.hh>
#include <render/map_renderer.hh>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace editor
{
int run(const util::CommandLine &args, GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    ImGuiIO &io = ImGui::GetIO();

    data::Map *map = nullptr;

    render::MapRenderer renderer(800, 600);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(0);
        if(map)
            renderer.render(*map);
        glBindProgramPipeline(0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(ImGui::BeginMainMenuBar()) {
            if(ImGui::BeginMenu("File")) {
                if(ImGui::MenuItem("Load sandbox.json") && !map) {
                    map = new data::Map();
                    if(!map->loadFromFile("maps/sandbox.json")) {
                        delete map;
                        map = nullptr;
                    }
                }
                if(ImGui::MenuItem("Unload map") && map) {
                    delete map;
                    map = nullptr;
                }
                if(ImGui::MenuItem("Exit", "Alt+F4"))
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
} // namespace editor
