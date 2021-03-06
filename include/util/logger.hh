/*
 * logger.hh
 * Created: 2021-01-16, 21:28:14.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/format.hh>

namespace util
{
void log(const std::string &str);

template<typename... Args>
static inline constexpr void log(const std::string &fmt, Args... args)
{
    log(util::format(fmt, args...));
}

template<typename... Args>
static inline constexpr void dlog(const std::string &fmt, Args... args)
{
#ifndef NDEBUG
    log(util::format(fmt, args...));
#endif
}

const std::string &getLastLog();
} // namespace util
