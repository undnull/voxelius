/*
 * menu_bar.hh
 * Created: 2021-03-05, 22:07:23.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/clock.hh>

#include <imgui.h>

namespace editor
{
class MenuBar final {
public:
    void render(const ImGuiIO &io);

private:
    util::Clock fps_clock;
    float fps_framerate = 0.0f;
    float fps_frametime = 0.0f;
    bool fps_visible = true;

public:
    bool open_map = false;
    bool open_script = false;
    bool open_shader = false;
    bool close_opened = false;
    bool save_opened = false;
    bool save_as_opened = false;
    bool should_exit = false;
};
} // namespace editor
