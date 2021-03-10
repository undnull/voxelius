/*
 * fs.hh
 * Created: 2021-01-16, 21:14:19.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <common.hh>

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace util
{
const std::string readTextFile(const fs::path &path);
const std::vector<uint8_t> readBinaryFile(const fs::path &path);
void writeTextFile(const fs::path &path, const std::string &str);
} // namespace util
