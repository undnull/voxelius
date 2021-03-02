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

    void attach(unsigned int attachment, const Texture &texture, unsigned int level);

    bool isComplete();

    constexpr unsigned int get() const;

private:
    unsigned int framebuffer;
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

inline void Framebuffer::attach(unsigned int attachment, const Texture &texture, unsigned int level)
{
    glNamedFramebufferTexture(framebuffer, attachment, texture.get(), level);
}

inline bool Framebuffer::isComplete()
{
    return glCheckNamedFramebufferStatus(framebuffer, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

inline constexpr unsigned int Framebuffer::get() const
{
    return framebuffer;
}
} // namespace gfx
