/*
 * file.hh
 * Created: 2021-01-16, 21:14:19.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_UTIL_FILE_HH
#define VOXELIUS_UTIL_FILE_HH 1
#include <voxelius/types.hh>
#include <string>
#include <vector>

namespace util
{
    bool file_exists(const char *filename);
    const std::string file_read_txt(const char *filename);
    const std::vector<uint8_t> file_read_bin(const char *filename);
}

#endif
