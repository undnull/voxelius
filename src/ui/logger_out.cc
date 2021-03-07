/*
 * logger_out.cc
 * Created: 2021-03-06, 22:54:34.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <ui/logger_out.hh>
#include <util/logger.hh>

namespace ui
{
static constexpr ImGuiWindowFlags FLAGS = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
static constexpr float TEXT_PADDING = 15.0f;

void LoggerOut::draw(const ImGuiIO &io)
{
    const std::string str = util::getLastLog();
    const ImVec2 display_size = io.DisplaySize;
    const ImVec2 text_size = ImGui::CalcTextSize(str.c_str());
    if(ImGui::Begin("##logger_out", nullptr, FLAGS)) {
        ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Once);
        ImGui::SetWindowSize(display_size, ImGuiCond_Once);
        ImGui::SetCursorPos(util::getVec2(util::getVec2(display_size) - util::getVec2(text_size) - TEXT_PADDING));
        ImGui::Text("%s", str.c_str());
    }
    ImGui::End();
}
} // namespace ui
