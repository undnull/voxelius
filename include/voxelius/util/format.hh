/*
 * format.hh
 * Created: 2021-01-16, 21:24:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_UTIL_FORMAT_HH
#define VOXELIUS_UTIL_FORMAT_HH 1
#include <stdio.h>
#include <string>
#include <vector>

namespace util
{
    template<typename... Args>
    static inline constexpr const std::string format(const std::string &fmt, Args... args)
    {
        const int count = snprintf(nullptr, 0, fmt.c_str(), args...);
        if(count <= 0)
            return fmt;
        
        std::vector<char> buffer((size_t)count + 1);
        snprintf(buffer.data(), buffer.size(), fmt.c_str(), args...);

        return std::string(buffer.data());
    }
}

#endif
