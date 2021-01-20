/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/window.hh>
#include <glad/glad.h>

int main(void)
{
    if(!window::init())
        return 1;

    // Everything related to OpenGL wrappers should
    // be created INSIDE this scope so we safely
    // release everything before destroying the window
    // with the context using the AD (see window.cc) class.
    {
        while(window::is_open()) {
            window::begin_frame();
            glClear(GL_COLOR_BUFFER_BIT);
            window::end_frame();
        }
    }

    return 0;
}
