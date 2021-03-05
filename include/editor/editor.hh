/*
 * editor.hh
 * Created: 2021-03-05, 19:09:13.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/commandline.hh>

struct GLFWwindow;

namespace editor
{
int run(const util::CommandLine &args, GLFWwindow *window);
} // namespace editor
