/*
 * map_editor.hh
 * Created: 2021-03-06, 16:31:24.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <render/map_renderer.hh>
#include <util/fs.hh>
#include <imgui.h>

namespace editor
{
bool loadMap(const fs::path &path);
void saveMap();
void saveMap(const fs::path &path);

void packMap(const fs::path &path);

void drawMapEditor(const ImGuiIO &io, render::MapRenderer &renderer);
} // namespace editor
