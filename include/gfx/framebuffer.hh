/*
 * framebuffer.hh
 * Created: 2021-03-02, 22:30:07.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gfx/texture.hh>

namespace gfx
{
class Framebuffer final {
public:
    Framebuffer();
    Framebuffer(Framebuffer &&rhs);
    Framebuffer(const Framebuffer &rhs) = delete;

    ~Framebuffer();

    Framebuffer &operator=(Framebuffer &&rhs);
    Framebuffer &operator=(const Framebuffer &rhs) = delete;

    void attach(GLenum attachment, const Texture &texture, GLint level);

    bool isComplete();

    constexpr GLuint get() const;

private:
    GLuint framebuffer;
};

inline Framebuffer::Framebuffer()
{
    glCreateFramebuffers(1, &framebuffer);
}

inline Framebuffer::Framebuffer(Framebuffer &&rhs)
{
    framebuffer = rhs.framebuffer;
    rhs.framebuffer = 0;
}

inline Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &framebuffer);
}

inline Framebuffer &Framebuffer::operator=(Framebuffer &&rhs)
{
    Framebuffer copy(std::move(rhs));
    std::swap(copy.framebuffer, framebuffer);
    return *this;
}

inline void Framebuffer::attach(GLenum attachment, const Texture &texture, GLint level)
{
    glNamedFramebufferTexture(framebuffer, attachment, texture.get(), level);
}

inline bool Framebuffer::isComplete()
{
    return glCheckNamedFramebufferStatus(framebuffer, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

inline constexpr GLuint Framebuffer::get() const
{
    return framebuffer;
}
} // namespace gfx
