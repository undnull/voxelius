/*
 * file.hh
 * Created: 2021-01-16, 21:14:19.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef UTIL_FILE_HH
#define UTIL_FILE_HH 1
#include <types.hh>

#include <string>
#include <vector>

namespace util
{
bool fileExists(const char *filename);
const std::string readTextFile(const char *filename);
const std::vector<uint8_t> readBinaryFile(const char *filename);
} // namespace util

#endif
