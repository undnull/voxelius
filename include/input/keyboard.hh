/*
 * keyboard.hh
 * Created: 2021-03-10, 14:50:21.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <GLFW/glfw3.h>

namespace input
{
extern bool keys_down[];
extern int pressed_key, released_key;

void keyCallback(int key, int action);

inline bool isKeyPressed(int key)
{
    return keys_down[key];
}

inline bool isKeyJustPressed(int key)
{
    return pressed_key == key;
}

inline bool isKeyJustReleased(int key)
{
    return released_key == key;
}
} // namespace input
