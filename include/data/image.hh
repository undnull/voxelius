/*
 * image.hh
 * Created: 2021-03-10, 08:53:03.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <common.hh>
#include <util/fs.hh>

#include <glad/glad.h>
#include <stb_image.h>

namespace data
{
class Image {
public:
    Image();
    Image(Image &&rhs);
    Image(const Image &rhs) = delete;

    Image &operator=(Image &&rhs);
    Image &operator=(const Image &rhs) = delete;

    virtual ~Image();

    void clear();
    bool loadFromFile(const fs::path &path);

    constexpr int getWidth() const;
    constexpr int getHeight() const;
    constexpr void getSize(int &width, int &height) const;

    constexpr const void *getPixels() const;

public:
    static const GLenum TEXTURE_FORMAT = GL_RGBA;
    static const GLenum TEXTURE_TYPE = GL_UNSIGNED_BYTE;

private:
    int width, height, comp;
    void *pixels;
};

inline Image::Image()
{
    width = -1;
    height = -1;
    comp = -1;
    pixels = nullptr;
}

inline Image::Image(Image &&rhs)
{
    width = rhs.width;
    height = rhs.height;
    comp = rhs.comp;
    pixels = rhs.pixels;
    rhs.width = -1;
    rhs.height = -1;
    rhs.comp = -1;
    rhs.pixels = nullptr;
}

inline Image::~Image()
{
    stbi_image_free(pixels);
}

inline Image &Image::operator=(Image &&rhs)
{
    Image copy(std::move(rhs));
    std::swap(copy.width, width);
    std::swap(copy.height, height);
    std::swap(copy.comp, comp);
    std::swap(copy.pixels, pixels);
    return *this;
}

inline void Image::clear()
{
    stbi_image_free(pixels);
    width = -1;
    height = -1;
    comp = -1;
    pixels = nullptr;
}

inline bool Image::loadFromFile(const fs::path &path)
{
    // make sure we don't leak the memory
    stbi_image_free(pixels);

    pixels = stbi_load(path.string().c_str(), &width, &height, &comp, STBI_rgb_alpha);
    return !!pixels;
}

inline constexpr int Image::getWidth() const
{
    return width;
}

inline constexpr int Image::getHeight() const
{
    return height;
}

inline constexpr void Image::getSize(int &width, int &height) const
{
    width = this->width;
    height = this->height;
}

inline constexpr const void *Image::getPixels() const
{
    return pixels;
}
} // namespace data
