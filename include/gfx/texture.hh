/*
 * texture.hh
 * Created: 2021-03-02, 09:37:49.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>
#include <glad/glad.h>

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

    void setParameter(unsigned int pname, int value);
    void setParameter(unsigned int pname, float value);

    void generateMipmap();

    constexpr unsigned int get() const;

private:
    unsigned int texture;
};

inline Texture::Texture()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
}

inline Texture::Texture(Texture &&rhs)
{
    texture = rhs.texture;
    rhs.texture = 0;
}

inline Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

inline Texture &Texture::operator=(Texture &&rhs)
{
    Texture copy(std::move(rhs));
    std::swap(copy.texture, texture);
    return *this;
}

inline void Texture::resize(int width, int height, unsigned int format)
{
    glTextureStorage2D(texture, 1, format, width, height);
}

inline void Texture::write(int width, int height, unsigned int format, unsigned int type, const void *pixels)
{
    glTextureSubImage2D(texture, 0, 0, 0, width, height, format, type, pixels);
}

inline void Texture::setParameter(unsigned int pname, int value)
{
    glTextureParameteri(texture, pname, value);
}

inline void Texture::setParameter(unsigned int pname, float value)
{
    glTextureParameterf(texture, pname, value);
}

inline void Texture::generateMipmap()
{
    glGenerateTextureMipmap(texture);
}

inline constexpr unsigned int Texture::get() const
{
    return texture;
}
} // namespace gfx
