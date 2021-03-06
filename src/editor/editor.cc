/*
 * editor.cc
 * Created: 2021-03-05, 19:38:48.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <editor/editor.hh>
#include <editor/menu_bar.hh>
#include <editor/file_browser.hh>
#include <editor/logger_out.hh>
#include <util/logger.hh>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace editor
{
int run(const util::CommandLine &args, GLFWwindow *window)
{
    glfwSetWindowTitle(window, "Voxelius (Editor)");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    LoggerOut logger_out;

    MenuBar menu_bar;
    FileBrowserDialog open_dialog("Open file##open_dialog");

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        logger_out.draw(io);

        menu_bar.draw(io);

        if(open_dialog.draw(io, menu_bar.file_open))
            util::log("file open stub for %s", open_dialog.getPath().string().c_str());
        menu_bar.file_open = false;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(menu_bar.file_exit)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
} // namespace editor
