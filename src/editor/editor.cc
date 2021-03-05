/*
 * editor.cc
 * Created: 2021-03-05, 19:38:48.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <editor/editor.hh>
#include <editor/menu_bar.hh>
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
    MenuBar menu_bar;

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        menu_bar.render(io);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(menu_bar.wants_exit)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
} // namespace editor
