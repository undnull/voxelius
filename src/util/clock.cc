/*
 * clock.cc
 * Created: 2021-03-02, 22:56:36.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <util/clock.hh>
#include <GLFW/glfw3.h>

namespace util
{
Clock::Clock()
{
    start = static_cast<float>(glfwGetTime());
}

float Clock::getTime() const
{
    return static_cast<float>(glfwGetTime()) - start;
}

float Clock::reset()
{
    float cur_time = static_cast<float>(glfwGetTime());
    float delta = cur_time - start;
    start = cur_time;
    return delta;
}
} // namespace util
