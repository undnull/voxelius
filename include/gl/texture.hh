/*
 * texture.hh
 * Created: 2021-01-19, 14:54:44.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <gl/object.hh>
#include <types.hh>

namespace gl
{
class Texture final : public Object {
public:
    Texture();
    ~Texture();

    void create() override;
    void release() override;
    bool isGood() const override;

    void setRepeat(bool enable);
    void setFilter(bool enable);

    template<typename T>
    void loadRGBA(int width, int height, const void *data);

    inline constexpr unsigned int getTexture() const
    {
        return texture;
    }

private:
    unsigned int texture;
};
} // namespace gl
