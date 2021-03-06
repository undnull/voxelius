/*
 * fs.hh
 * Created: 2021-01-16, 21:14:19.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace util
{
const std::string readTextFile(const char *filename);
const std::vector<uint8_t> readBinaryFile(const char *filename);
} // namespace util
