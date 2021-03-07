/*
 * fs.cc
 * Created: 2021-01-16, 21:17:06.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <util/fs.hh>

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

namespace util
{
const std::string readTextFile(const fs::path &path)
{
    std::ifstream ifs(path, std::ios::in);
    if(!ifs.good())
        return std::string();

    std::stringstream ss;
    ss << ifs.rdbuf();

    return ss.str();
}

const std::vector<uint8_t> readBinaryFile(const fs::path &path)
{
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    if(!ifs.good())
        return std::vector<uint8_t>();

    ifs.unsetf(std::ios::skipws);

    std::vector<uint8_t> buffer;

    ifs.seekg(0, std::ios::end);
    buffer.reserve(ifs.tellg());
    ifs.seekg(0, std::ios::beg);

    buffer.insert(buffer.begin(), std::istream_iterator<uint8_t>(ifs), std::istream_iterator<uint8_t>());
    return buffer;
}

void writeTextFile(const fs::path &path, const std::string &str)
{
    std::ofstream ofs(path, std::ios::out);
    if(ofs.good())
        ofs << str;
}
} // namespace util
