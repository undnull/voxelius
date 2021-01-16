/*
 * logger.hh
 * Created: 2021-01-16, 21:28:14.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_LOGGER_HH
#define VOXELIUS_LOGGER_HH 1
#include <voxelius/util/format.hh>

namespace logger
{
    namespace detail { void log(const std::string &str); }

    template<typename... Args>
    static inline constexpr void log(const std::string &fmt, Args... args)
    {
        detail::log(util::format(fmt, args...));
    }

    template<typename... Args>
    static inline constexpr void dlog(const std::string &fmt, Args... args)
    {
#ifndef NDEBUG
        detail::log(util::format(fmt, args...));
#endif
    }
}

#endif
