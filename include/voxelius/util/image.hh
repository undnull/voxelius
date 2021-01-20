/*
 * image.hh
 * Created: 2021-01-20, 14:20:25.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_UTIL_IMAGE_HH
#define VOXELIUS_UTIL_IMAGE_HH 1

namespace util
{
    class Image final {
    public:
        Image();
        ~Image();

        bool load(const char *filename);
        void release();
        bool is_good() const;

        const char * get_error() const;

        inline constexpr unsigned char * get_pixels() const
        {
            return pixels;
        }

        inline constexpr int get_width() const
        {
            return width;
        }

        inline constexpr int get_height() const
        {
            return height;
        }

    private:
        unsigned char *pixels;
        int width, height;
    };
}

#endif
