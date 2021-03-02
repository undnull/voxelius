/*
 * texture.cc
 * Created: 2021-03-02, 09:41:22.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <gfx/texture.hh>

#include <glad/glad.h>

namespace gfx
{
Texture::Texture()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
}

Texture::Texture(Texture &&rhs)
{
    texture = rhs.texture;
    rhs.texture = 0;
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

Texture &Texture::operator=(Texture &&rhs)
{
    Texture copy(std::move(rhs));
    std::swap(copy.texture, texture);
    return *this;
}

void Texture::resize(int width, int height, unsigned int format)
{
    glTextureStorage2D(texture, 1, format, width, height);
}

void Texture::write(int width, int height, unsigned int format, unsigned int type, const void *pixels)
{
    glTextureSubImage2D(texture, 0, 0, 0, width, height, format, type, pixels);
}

void Texture::generateMipmap()
{
    glGenerateTextureMipmap(texture);
}

void Texture::setParameter(unsigned int param, int value)
{
    glTextureParameteri(texture, param, value);
}
} // namespace gfx
