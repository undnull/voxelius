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
    const bool init();

    const bool is_open();
    void close();

    void begin_frame();
    void end_frame();

    GLFWwindow * get_window();
}

#endif
