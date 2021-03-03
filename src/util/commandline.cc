/*
 * commandline.cc
 * Created: 2021-01-30, 14:52:00
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <util/commandline.hh>

#include <string.h>
#include <string>
#include <vector>

namespace util
{
static inline const bool isOption(const char *option)
{
    if(!option || *option != '-')
        return false;
    while(*option)
        option++;
    return option[-1] != '-';
}

CommandLine::CommandLine(int argc, char **argv)
    : options()
{
    for(int i = 1; i < argc; i++) {
        if(isOption(argv[i])) {
            option opt;
            opt.opt = argv[i];
            opt.has_argument = false;
            int j = i + 1;
            if(j < argc && !isOption(argv[j])) {
                opt.has_argument = true;
                opt.argument = argv[j];
                i++;
            }
            options.push_back(opt);
        }
    }
}

bool CommandLine::hasOption(const char *opt)
{
    for(const auto &it : options) {
        if(it.opt == opt)
            return true;
    }
    return false;
}

bool CommandLine::hasArgument(const char *opt)
{
    for(const auto &it : options) {
        if(it.opt == opt && it.has_argument)
            return true;
    }
    return false;
}

const char *CommandLine::getArgument(const char *opt)
{
    for(const auto &it : options) {
        if(it.opt == opt && it.has_argument)
            return it.argument.c_str();
    }
    return nullptr;
}
} // namespace util
