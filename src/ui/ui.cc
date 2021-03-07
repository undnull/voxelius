/*
 * ui.cc
 * Created: 2021-03-07, 12:33:25.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <ui/ui.hh>

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ui
{
void init(const util::CommandLine &args, GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    if(args.hasOption("--uistyle-classic"))
        ImGui::StyleColorsClassic();
    else if(args.hasOption("--uistyle-light"))
        ImGui::StyleColorsLight();
    else
        ImGui::StyleColorsDark();

    // FIXME: install the callback manually
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
}

const ImGuiIO &beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    return ImGui::GetIO();
}

void endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
} // namespace ui
