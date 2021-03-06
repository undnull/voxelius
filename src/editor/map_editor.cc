/*
 * map_editor.cc
 * Created: 2021-03-06, 16:36:04.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <editor/map_editor.hh>
#include <imgui_stdlib.h>

namespace editor
{
static const ImVec2 GLTEX_UV0 = ImVec2(0.0f, 1.0f);
static const ImVec2 GLTEX_UV1 = ImVec2(1.0f, 0.0f);

static fs::path map_path;
static data::Map map;

bool loadMap(const fs::path &path)
{
    map.clear();
    return map.loadFromFile(path, false);
}

void saveMap()
{

}

void saveMap(const fs::path &path)
{

}

void packMap(const fs::path &path)
{

}

void drawMapEditor(const ImGuiIO &io, render::MapRenderer &renderer)
{
    const float2_t size = renderer.getTargetSize() * 0.5f;
    renderer.render(map);
    if(ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Image(reinterpret_cast<ImTextureID>(renderer.getColorTarget().get()), ImVec2(size.x, size.y), GLTEX_UV0, GLTEX_UV1);
    }
    ImGui::End();
}
} // namespace editor
