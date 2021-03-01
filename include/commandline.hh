/*
 * commandline.hh
 * Created: 2021-01-30, 14:49:00
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef COMMANDLINE_HH
#define COMMANDLINE_HH 1
#include <string>
#include <vector>

class CommandLine final {
public:
    struct option final {
        std::string opt;
        std::string argument;
        bool has_argument;
    };

public:
    CommandLine(int argc, char **argv);

    bool hasOption(const char *option);
    bool hasArgument(const char *option);
    const char *getArgument(const char *option);

private:
    std::vector<option> options;
};

#endif
