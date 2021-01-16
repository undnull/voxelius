/*
 * logger.cc
 * Created: 2021-01-16, 21:30:28.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/logger.hh>
#include <time.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>

namespace logger
{
    static std::mutex mutex;
    static std::ofstream logfile("./voxelius.log", std::ios::out | std::ios::app);

    void detail::log(const std::string &str)
    {
        std::lock_guard<std::mutex> al(mutex);

        char datetime[40] = { 0 };
        time_t cur_time = time(nullptr);
        strftime(datetime, sizeof(datetime), "[%Y-%m-%d, %H:%M:%S]", localtime(&cur_time));

        std::stringstream ss;
        ss << datetime;
        ss << " ";
        ss << str;

        if(logfile.good()) logfile << ss.str() << std::endl;
        if(std::cerr.good()) std::cerr << ss.str() << std::endl;
    }
}
