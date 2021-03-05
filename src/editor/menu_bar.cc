/*
 * menu_bar.cc
 * Created: 2021-03-05, 22:07:53.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <config.hh>
#include <editor/menu_bar.hh>

namespace editor
{
void MenuBar::render(const ImGuiIO &io)
{
    if(fps_clock.getTime() >= 0.05f) {
        fps_framerate += io.Framerate;
        fps_framerate /= 2.0f;
        fps_frametime += io.DeltaTime * 1000.0f;
        fps_frametime /= 2.0f;
        fps_clock.reset();
    }

    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("Exit", "Alt+F4"))
                wants_exit = true;
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View")) {
            ImGui::MenuItem("WIP");
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help")) {
            ImGui::MenuItem("WIP");
            ImGui::Separator();
            ImGui::MenuItem("Voxelius " VERSION_STRING, nullptr, false, false);
            ImGui::EndMenu();
        }

        ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("FPS: FFFF.ff time: DDDD.ddms").x * 1.025f);
        ImGui::Text("FPS: %.02f time: %2.02fms", fps_framerate, fps_frametime);

        ImGui::EndMainMenuBar();
    }
}
} // namespace editor
