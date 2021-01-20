/*
 * image.cc
 * Created: 2021-01-20, 14:22:19.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/util/image.hh>
#include <stb_image.h>

namespace util
{
    Image::Image() : pixels(nullptr), width(0), height(0)
    {

    }

    Image::~Image()
    {
        release();
    }

    bool Image::load(const char *filename)
    {
        release();
        int comp;
        stbi_set_flip_vertically_on_load(1);
        pixels = stbi_load(filename, &width, &height, &comp, STBI_rgb_alpha);
        return pixels && width > 0 && height > 0;
    }

    void Image::release()
    {
        if(pixels) {
            stbi_image_free(pixels);
            pixels = nullptr;
            width = 0;
            height = 0;
        }
    }

    bool Image::is_good() const
    {
        return pixels && width > 0 && height > 0;
    }

    const char * Image::get_error() const
    {
        return stbi_failure_reason();
    }
}
