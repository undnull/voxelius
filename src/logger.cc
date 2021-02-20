/*
 * logger.cc
 * Created: 2021-01-16, 21:30:28.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/logger.hh>

#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <time.h>

namespace logger
{
static std::mutex mutex;
static std::ofstream logfile("./voxelius.log", std::ios::out | std::ios::app);
static std::ofstream logfile_l("./voxelius.latest.log", std::ios::out);

void log(const std::string &str)
{
    std::lock_guard<std::mutex> al(mutex);

    char datetime[40] = { 0 };
    time_t cur_time = time(nullptr);
    strftime(datetime, sizeof(datetime), "[%Y-%m-%d, %H:%M:%S]", localtime(&cur_time));

    std::stringstream ss;
    ss << datetime;
    ss << " ";
    ss << str;

    std::cerr << ss.str() << std::endl;
    logfile << ss.str() << std::endl;
    logfile_l << ss.str() << std::endl;
}
} // namespace logger
