/*
 * window.hh
 * Created: 2021-01-16, 15:37:44.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_WINDOW_HH
#define VOXELIUS_WINDOW_HH 1

struct GLFWwindow;

namespace window
{
bool init();

bool isOpen();
void close();

void beginFrame();
void endFrame();

GLFWwindow *getWindow();

void getSize(int &width, int &height);
} // namespace window

#endif
