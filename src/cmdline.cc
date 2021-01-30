/*
 * cmdline.cc
 * Created: 2021-01-30, 14:52:thth
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/cmdline.hh>
#include <string.h>
#include <string>
#include <vector>

namespace cmdline
{
    struct option final {
        std::string opt;
        std::string argument;
        bool has_argument;
    };

    static std::vector<option> options;

    static inline const bool is_option(const char *option)
    {
        if(!option || *option != '-')
            return false;
        while(*option)
            option++;
        return option[-1] != '-';
    }

    void init(int argc, char **argv)
    {
        for(int i = 1; i < argc; i++) {
            if(is_option(argv[i])) {
                option opt;
                opt.opt = argv[i];
                opt.has_argument = false;
                int j = i + 1;
                if(j < argc && !is_option(argv[j])) {
                    opt.has_argument = true;
                    opt.argument = argv[j];
                    i++;
                }
                options.push_back(opt);
            }
        }
    }
    
    bool has_option(const char *opt)
    {
        for(const auto &it : options) {
            if(it.opt == opt)
                return true;
        }
        return false;
    }

    bool has_argument(const char *opt)
    {
        for(const auto &it : options) {
            if(it.opt == opt && it.has_argument)
                return true;
        }
        return false;
    }
    
    const char * get_argument(const char *opt)
    {
        for(const auto &it : options) {
            if(it.opt == opt && it.has_argument)
                return it.argument.c_str();
        }
        return nullptr;
    }
}
