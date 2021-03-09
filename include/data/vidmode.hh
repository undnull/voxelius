/*
 * vidmode.hh
 * Created: 2021-03-07, 12:47:41.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/command_line.hh>
#include <util/fs.hh>

struct GLFWmonitor;

namespace data
{
class VidMode {
public:
    VidMode();

    bool loadFromFile(const fs::path &path);
    void loadFromArgs(const util::CommandLine &args);

    void saveToFile(const fs::path &path);

public:
    int width;
    int height;
    int border;
    int swap_interval;
    GLFWmonitor *monitor;
};
} // namespace data
