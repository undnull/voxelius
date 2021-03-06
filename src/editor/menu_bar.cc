/*
 * menu_bar.cc
 * Created: 2021-03-05, 22:07:53.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <config.hh>
#include <editor/menu_bar.hh>
#include <util/clock.hh>
#include <GLFW/glfw3.h>

namespace editor
{
static util::Clock fps_clock;
static float fps_framerate = 0.0f;
static float fps_frametime = 0.0f;
static bool fps_visible = true;

bool menu_bar_open_map = false;
bool menu_bar_open_script = false;
bool menu_bar_open_shader = false;
bool menu_bar_new_map = false;
bool menu_bar_new_script = false;
bool menu_bar_new_shader = false;
bool menu_bar_close = false;
bool menu_bar_save = false;
bool menu_bar_save_as = false;
bool menu_bar_exit = false;

void drawMenuBar(const ImGuiIO &io)
{
    if(fps_clock.getTime() >= 0.025f) {
        fps_framerate += io.Framerate;
        fps_framerate /= 2.0f;
        fps_frametime += io.DeltaTime * 1000.0f;
        fps_frametime /= 2.0f;
        fps_clock.reset();
    }

    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::BeginMenu("Open")) {
                menu_bar_open_map = ImGui::MenuItem("Map", "Ctrl+M");
                menu_bar_open_script = ImGui::MenuItem("Script", "WIP");
                menu_bar_open_shader = ImGui::MenuItem("Shader", "WIP");
                ImGui::EndMenu();
            }
            menu_bar_close = ImGui::MenuItem("Close", "WIP");
            ImGui::Separator();
            if(ImGui::BeginMenu("New")) {
                menu_bar_new_map = ImGui::MenuItem("Map", "WIP_NEW");
                menu_bar_new_script = ImGui::MenuItem("Script", "WIP_NEW");
                menu_bar_new_shader = ImGui::MenuItem("Shader", "WIP_NEW");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            menu_bar_save = ImGui::MenuItem("Save", "WIP");
            menu_bar_save_as = ImGui::MenuItem("Save as", "WIP");
            ImGui::Separator();
            menu_bar_exit = ImGui::MenuItem("Exit", "Shift+Esc");
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View")) {
            ImGui::MenuItem("FPS counter", nullptr, &fps_visible);
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help")) {
            ImGui::MenuItem("Voxelius " VERSION_STRING, nullptr, false, false);
            ImGui::EndMenu();
        }

        if(fps_visible) {
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("DDDD.ddd ms/frame (DDDD.dd FPS)").x * 1.025f);
            ImGui::Text("%4.03f ms/frame (%4.02f FPS)", fps_frametime, fps_framerate);
        }

        ImGui::EndMainMenuBar();
    }

    if(io.KeyCtrl && io.KeysDown[GLFW_KEY_M])
        menu_bar_open_map = true;
    if(io.KeyShift && io.KeysDown[GLFW_KEY_ESCAPE])
        menu_bar_exit = true;
}
} // namespace editor
