/*
 * texture.cc
 * Created: 2021-01-19, 15:04:24.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <gl/texture.hh>

#include <glad/glad.h>

namespace gl
{
Texture::Texture() :
    texture(0)
{
    create();
    setRepeat(false);
    setFilter(false);
}

Texture::~Texture()
{
    release();
}

void Texture::create()
{
    release();
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
}

void Texture::release()
{
    if(texture) {
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

bool Texture::isGood() const
{
    return texture != 0;
}

void Texture::setRepeat(bool enable)
{
    unsigned int param = enable ? GL_REPEAT : GL_CLAMP_TO_EDGE;
    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, param);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, param);
}

void Texture::setFilter(bool enable)
{
    unsigned int param = enable ? GL_LINEAR : GL_NEAREST;
    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, param);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, param);
}

template<>
void Texture::loadRGBA<uint8_t>(int width, int height, const void *data)
{
    glTextureStorage2D(texture, 1, GL_RGBA16F, width, height);
    glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
} // namespace gl
