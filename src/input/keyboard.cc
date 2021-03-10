/*
 * keyboard.cc
 * Created: 2021-03-10, 15:06:08.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <input/keyboard.hh>

namespace input
{
bool keys_down[GLFW_KEY_LAST + 1] = { 0 };
int pressed_key = GLFW_KEY_UNKNOWN;
int released_key = GLFW_KEY_UNKNOWN;

void keyCallback(int key, int action)
{
    bool press = (action == GLFW_PRESS || action == GLFW_REPEAT);
    keys_down[key] = press;
    if(press)
        pressed_key = key;
    else
        released_key = key;
}
} // namespace input
