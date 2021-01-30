/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/client/client.hh>
#include <voxelius/cmdline.hh>

int main(int argc, char **argv)
{
    cmdline::init(argc, argv);

    if(!client::init())
        return 1;
    
    return client::run();
}
