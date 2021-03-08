/*
 * vidmode.cc
 * Created: 2021-03-07, 12:49:57.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/vidmode.hh>
#include <util/json.hh>
#include <util/logger.hh>

#include <GLFW/glfw3.h>
#include <stdlib.h>

namespace data
{
VidMode::VidMode()
{
    width = 800;
    height = 600;
    border = GLFW_TRUE;
    swap_interval = 0;
    monitor = nullptr;
}

bool VidMode::loadFromFile(const fs::path &path)
{
    if(!fs::exists(path)) {
        util::log("vidmode: file %s doesn't exist", path.string().c_str());
        return false;
    }

    try {
        const json j = json::parse(util::readTextFile(path));

        width = util::jsonRequire(j, "width")->get<int>();
        height = util::jsonRequire(j, "height")->get<int>();
        border = util::jsonRequire(j, "border")->get<bool>() ? GLFW_TRUE : GLFW_FALSE;
        swap_interval = util::jsonRequire(j, "vsync")->get<bool>() ? 1 : 0;
        if(util::jsonRequire(j, "fullscreen")->get<bool>())
            monitor = glfwGetPrimaryMonitor();

        return true;
    }
    catch(const std::exception &e) {
        util::log("vidmode: %s", e.what());
        return false;
    }
}

void VidMode::loadFromArgs(const util::CommandLine &args)
{
    if(args.hasArgument("--width") && args.hasArgument("--height")) {
        width = atoi(args.getArgument("--width"));
        height = atoi(args.getArgument("--height"));
    }
    else if(args.hasOption("--native")) {
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        width = mode->width;
        height = mode->height;
    }

    border = args.hasOption("--noborder") ? GLFW_FALSE : border;
    
    if(args.hasOption("--no-vsync"))
        swap_interval = 0;
    else if(args.hasOption("--vsync"))
        swap_interval = 1;

    if(args.hasOption("--windowed"))
        monitor = nullptr;
    else if(args.hasOption("--fullscreen"))
        monitor = glfwGetPrimaryMonitor();
}

void VidMode::saveToFile(const fs::path &path)
{
    try {
        json j;
        j["width"] = width;
        j["height"] = height;
        j["border"] = (border == GLFW_TRUE);
        j["vsync"] = (swap_interval == 1);
        j["fullscreen"] = (monitor != nullptr);
        util::writeTextFile(path, j.dump(4));
    }
    catch(const std::exception &e) {
        util::log("vidmode: %s", e.what());
    }
}
} // namespace data
