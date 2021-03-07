/*
 * ui.hh
 * Created: 2021-03-07, 12:31:49.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/command_line.hh>
#include <util/imgui.hh>

struct GLFWwindow;

namespace ui
{
void init(const util::CommandLine &args, GLFWwindow *window);
const ImGuiIO &beginFrame();
void endFrame();
} // namespace ui
