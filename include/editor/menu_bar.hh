/*
 * menu_bar.hh
 * Created: 2021-03-05, 22:07:23.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <imgui.h>

namespace editor
{
void drawMenuBar(const ImGuiIO &io);

extern bool menu_bar_open_map;
extern bool menu_bar_open_script;
extern bool menu_bar_open_shader;
extern bool menu_bar_new_map;
extern bool menu_bar_new_script;
extern bool menu_bar_new_shader;
extern bool menu_bar_close;
extern bool menu_bar_save;
extern bool menu_bar_save_as;
extern bool menu_bar_exit;
} // namespace editor
