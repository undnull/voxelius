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
MenuBar::MenuBar()
{
    file_open = false;
    file_close = false;
    file_new = false;
    file_save = false;
    file_save_as = false;
    file_exit = false;
    view_fps = true;

    fps_framerate = 0.0f;
    fps_frametime = 0.0f;
}

void MenuBar::draw(const ImGuiIO &io)
{
    if(fps_clock.getTime() >= 0.025f) {
        fps_framerate += io.Framerate;
        fps_framerate *= 0.5f;
        fps_frametime += io.DeltaTime * 1000.0f;
        fps_frametime *= 0.5f;
        fps_clock.reset();
    }

    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            file_open = ImGui::MenuItem("Open");
            file_close = ImGui::MenuItem("Close", nullptr, false, false);
            ImGui::Separator();
            file_new = ImGui::MenuItem("New", nullptr, false, false);
            ImGui::Separator();
            file_exit = ImGui::MenuItem("Exit", "Shift+Esc");
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View")) {
            if(ImGui::BeginMenu("Style")) {
                if(ImGui::MenuItem("StyleColorsClassic"))
                    ImGui::StyleColorsClassic();
                if(ImGui::MenuItem("StyleColorsDark"))
                    ImGui::StyleColorsDark();
                if(ImGui::MenuItem("StyleColorsLight"))
                    ImGui::StyleColorsLight();
                ImGui::EndMenu();
            }
            ImGui::Separator();
            ImGui::MenuItem("FPS counter", nullptr, &view_fps);
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help")) {
            ImGui::MenuItem("Voxelius " VERSION_STRING, nullptr, false, false);
            ImGui::EndMenu();
        }

        if(view_fps) {
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("DDDD.ddd ms/frame (DDDD.dd FPS)").x * 1.025f);
            ImGui::Text("%4.03f ms/frame (%4.02f FPS)", fps_frametime, fps_framerate);
        }

        ImGui::EndMainMenuBar();
    }

    file_exit = file_exit || (io.KeyShift && io.KeysDown[GLFW_KEY_ESCAPE]);
}
} // namespace editor
