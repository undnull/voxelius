/*
 * texture.hh
 * Created: 2021-03-02, 09:37:49.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace gfx
{
class Texture final {
public:
    Texture();
    Texture(Texture &&rhs);
    Texture(const Texture &rhs) = delete;

    ~Texture();

    Texture &operator=(Texture &&rhs);
    Texture &operator=(const Texture &rhs) = delete;

    void resize(int width, int height, unsigned int format);
    void write(int width, int height, unsigned int format, unsigned int type, const void *pixels);

    inline constexpr unsigned int get() const
    {
        return texture;
    }

private:
    unsigned int texture;
};
} // namespace gfx
