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

    bool is_open();
    void close();

    void begin_frame();
    void end_frame();

    GLFWwindow * get_window();

    void get_size(int &width, int &height);
}

#endif
