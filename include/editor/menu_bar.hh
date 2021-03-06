/*
 * menu_bar.hh
 * Created: 2021-03-05, 22:07:23.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/imgui.hh>
#include <util/clock.hh>

namespace editor
{
class MenuBar final {
public:
    MenuBar();

    void draw(const ImGuiIO &io);

public:
    bool file_open;
    bool file_close;
    bool file_new;
    bool file_save;
    bool file_save_as;
    bool file_exit;
    bool view_fps;
    bool view_taking_screenshot;

private:
    util::Clock fps_clock;
    float fps_framerate;
    float fps_frametime;
};
} // namespace editor
