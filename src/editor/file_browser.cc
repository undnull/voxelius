/*
 * file_browser.cc
 * Created: 2021-03-06, 13:06:46.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <editor/file_browser.hh>
#include <util/format.hh>
#include <imgui_stdlib.h>
#include <GLFW/glfw3.h>

namespace editor
{
FileBrowserDialog::FileBrowserDialog(const std::string &title) : title(title)
{
    visible = false;
    cwd = fs::current_path();
    selected = cwd;
    has_enumerated = false;
    has_filter = false;
}

void FileBrowserDialog::setFilter(const std::string &filter)
{
    this->filter = filter;
    has_filter = true;
}

void FileBrowserDialog::clearFilter()
{
    filter.clear();
    has_filter = false;
}

void FileBrowserDialog::close()
{
    visible = false;
}

bool FileBrowserDialog::draw(const ImGuiIO &io, bool show)
{
    if(!visible && show)
        visible = true;

    bool has_selected = false;

    if(visible && ImGui::Begin(title.c_str(), &visible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
        updateEntries(false);

        const std::string cwd_str = fs::canonical(cwd).string();
        const float width = glm::max(ImGui::CalcTextSize(cwd_str.c_str()).x, io.DisplaySize.x * 0.35f);

        ImGui::Text("%s", cwd_str.c_str());
        ImGui::Separator();

        ImGui::PushItemWidth(width);
        if(ImGui::ListBoxHeader("##file_list")) {
            for(const auto &it : entries) {
                if(ImGui::Selectable(it.print.c_str(), &it.selected, ImGuiSelectableFlags_AllowDoubleClick)) {
                    if(it.is_directory) {
                        cwd = it.path;
                        updateEntries(true);
                    }
                    else {
                        selected = it.path;
                        selected_str = it.path.filename().string();
                        has_selected = has_selected || ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left);
                    }
                }
            }
            ImGui::ListBoxFooter();
        }
        ImGui::Separator();
        ImGui::PopItemWidth();

        ImGui::PushItemWidth(width);
        ImGui::InputText("##file_name", &selected_str);
        ImGui::PopItemWidth();

        has_selected = has_selected || io.KeysDown[GLFW_KEY_ENTER] || io.KeysDown[GLFW_KEY_KP_ENTER];

        ImGui::End();
    }

    if(has_selected) {
        if(selected_str != selected.filename().string())
            selected = cwd / selected_str;
        visible = false;
        return true;
    }

    return false;
}

void FileBrowserDialog::updateEntries(bool updated)
{
    if(!has_enumerated || updated) {
        entries.clear();

        // FIXME: the root path enumeration on my machine yields
        // some crazy shit that segfaults the application with some
        // weird stuff in the debugger (path() returns weird shit).
        // So for now root_path is inaccessible all the time.
        if(cwd.has_parent_path() && cwd.root_path() != cwd.parent_path()) {
            fs_entry prev;
            prev.path = cwd.parent_path();
            prev.print = "D ..";
            prev.is_directory = true;
            prev.selected = false;
            entries.push_back(prev);
        }
        
        for(const auto &it : fs::directory_iterator(cwd)) {
            if(it.is_directory()) {
                fs_entry entry;
                entry.path = it.path();
                entry.print = "D " + it.path().filename().string();
                entry.is_directory = true;
                entry.selected = false;
                entries.push_back(entry);
            }
        }

        for(const auto &it : fs::directory_iterator(cwd)) {
            if(!it.is_directory()) {
                fs_entry entry;
                entry.path = it.path();
                entry.print = "F " + it.path().filename().string();
                entry.is_directory = false;
                entry.selected = false;
                if(!entry.is_directory && has_filter && entry.path.extension() != filter)
                    continue;
                entries.push_back(entry);
            }
        }

        has_enumerated = true;
    }
}
} // namespace editor
