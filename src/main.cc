/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/window.hh>

int main(void)
{
    if(!window::init())
        return 1;
    
    while(window::is_open()) {
        window::begin_frame();
        window::end_frame();
    }

    return 0;
}
