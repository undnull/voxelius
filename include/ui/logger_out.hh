/*
 * logger_out.hh
 * Created: 2021-03-06, 22:53:45.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/imgui.hh>

namespace ui
{
class LoggerOut {
public:
    void draw(const ImGuiIO &io);
};
} // namespace ui
