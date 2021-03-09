/*
 * command_line.hh
 * Created: 2021-01-30, 14:49:00
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <string>
#include <vector>

namespace util
{
class CommandLine {
public:
    struct option {
        std::string opt;
        std::string argument;
        bool has_argument;
    };

public:
    CommandLine(int argc, char **argv);

    bool hasOption(const char *option) const;
    bool hasArgument(const char *option) const;
    const char *getArgument(const char *option) const;

private:
    std::vector<option> options;
};
} // namespace util
