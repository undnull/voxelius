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
// clang-format off
// reason: color indentation
void applyStyle_cherry(ImGuiStyle &style)
{
    // https://github.com/ocornut/imgui/issues/707#issuecomment-430613104

    ImGui::StyleColorsDark(&style);

    constexpr auto color_fg_0 = [](float alpha) { return ImVec4(0.232f, 0.201f, 0.271f, alpha); };
    constexpr auto color_fg_1 = [](float alpha) { return ImVec4(0.455f, 0.198f, 0.301f, alpha); };
    constexpr auto color_fg_2 = [](float alpha) { return ImVec4(0.502f, 0.075f, 0.256f, alpha); };
    constexpr auto color_bg_0 = [](float alpha) { return ImVec4(0.200f, 0.220f, 0.270f, alpha); };
    constexpr auto color_text = [](float alpha) { return ImVec4(0.860f, 0.930f, 0.890f, alpha); };

    style.Colors[ImGuiCol_Text]                 = color_text(0.78f);
    style.Colors[ImGuiCol_TextDisabled]         = color_text(0.28f);
    style.Colors[ImGuiCol_WindowBg]             = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]              = color_bg_0(0.58f);
    style.Colors[ImGuiCol_PopupBg]              = color_bg_0(0.9f);
    style.Colors[ImGuiCol_Border]               = ImVec4(0.54f, 0.48f, 0.26f, 0.16f);
    style.Colors[ImGuiCol_BorderShadow]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]              = color_bg_0(1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]       = color_fg_1(0.78f);
    style.Colors[ImGuiCol_FrameBgActive]        = color_fg_1(1.00f);
    style.Colors[ImGuiCol_TitleBg]              = color_fg_0(1.00f);
    style.Colors[ImGuiCol_TitleBgActive]        = color_fg_2(1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]     = color_bg_0(0.75f);
    style.Colors[ImGuiCol_MenuBarBg]            = color_bg_0(0.47f);
    style.Colors[ImGuiCol_ScrollbarBg]          = color_bg_0(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = color_fg_1(0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = color_fg_1(1.00f);
    style.Colors[ImGuiCol_CheckMark]            = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]           = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_Button]               = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered]        = color_fg_1(0.86f);
    style.Colors[ImGuiCol_ButtonActive]         = color_fg_1(1.00f);
    style.Colors[ImGuiCol_Header]               = color_fg_1(0.76f);
    style.Colors[ImGuiCol_HeaderHovered]        = color_fg_1(0.86f);
    style.Colors[ImGuiCol_HeaderActive]         = color_fg_2(1.00f);
    style.Colors[ImGuiCol_Separator]            = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive]      = color_fg_1(1.00f);
    style.Colors[ImGuiCol_SeparatorHovered]     = color_fg_1(0.78f);
    style.Colors[ImGuiCol_ResizeGrip]           = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered]    = color_fg_1(0.78f);
    style.Colors[ImGuiCol_ResizeGripActive]     = color_fg_1(1.00f);
    style.Colors[ImGuiCol_PlotLines]            = color_text(0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered]     = color_fg_1(1.00f);
    style.Colors[ImGuiCol_PlotHistogram]        = color_text(0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = color_fg_1(1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]       = color_fg_1(0.43f);
    style.Colors[ImGuiCol_ModalWindowDimBg]     = color_bg_0(0.73f);

    style.WindowRounding = 0.0f;
    style.FrameRounding = 3.0f;
    style.ScrollbarRounding = 16.0f;
    style.GrabRounding = 2.0f;

    style.WindowPadding = ImVec2(6.0f, 4.0f);
    style.FramePadding = ImVec2(5.0f, 2.0f);

    style.ItemSpacing = ImVec2(7.0f, 1.0f);
    style.ItemInnerSpacing = ImVec2(1.0f, 1.0f);
    style.TouchExtraPadding = ImVec2(0.0f, 0.0f);
    style.IndentSpacing = 6.0f;

    style.ScrollbarSize = 12.0f;
    style.GrabMinSize = 20.0f;

    style.WindowTitleAlign.x = 0.50f;

    style.FrameBorderSize = 0.0f;
    style.WindowBorderSize = 1.0f;
}
// clang-format on

#if 0
// maybe later
void applyStyle_vgui(ImGuiStyle &style)
{
    // https://github.com/ocornut/imgui/issues/707#issuecomment-576867100

    style.Colors[ImGuiCol_Text]                     = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]             = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]                 = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]                  = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_PopupBg]                  = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_Border]                   = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    style.Colors[ImGuiCol_BorderShadow]             = ImVec4(0.14f, 0.16f, 0.11f, 0.52f);
    style.Colors[ImGuiCol_FrameBg]                  = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]           = ImVec4(0.27f, 0.30f, 0.23f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive]            = ImVec4(0.30f, 0.34f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_TitleBg]                  = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive]            = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]         = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    style.Colors[ImGuiCol_MenuBarBg]                = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]              = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab]            = ImVec4(0.28f, 0.32f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]     = ImVec4(0.25f, 0.30f, 0.22f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]      = ImVec4(0.23f, 0.27f, 0.21f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]                = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]               = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive]         = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    style.Colors[ImGuiCol_Button]                   = ImVec4(0.29f, 0.34f, 0.26f, 0.40f);
    style.Colors[ImGuiCol_ButtonHovered]            = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive]             = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    style.Colors[ImGuiCol_Header]                   = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered]            = ImVec4(0.35f, 0.42f, 0.31f, 0.60f);
    style.Colors[ImGuiCol_HeaderActive]             = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    style.Colors[ImGuiCol_Separator]                = ImVec4(0.14f, 0.16f, 0.11f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered]         = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive]          = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]               = ImVec4(0.19f, 0.23f, 0.18f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered]        = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive]         = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_Tab]                      = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_TabHovered]               = ImVec4(0.54f, 0.57f, 0.51f, 0.78f);
    style.Colors[ImGuiCol_TabActive]                = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused]             = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive]       = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]                = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]         = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]            = ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]     = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]           = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_DragDropTarget]           = ImVec4(0.73f, 0.67f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_NavHighlight]             = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight]    = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg]        = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]         = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style.FrameBorderSize = 1.0f;

    style.WindowRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.PopupRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;
}
#endif

void init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    applyStyle_cherry(ImGui::GetStyle());
    //applyStyle_vgui(ImGui::GetStyle());

    // FIXME: install the callbacks manually
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
