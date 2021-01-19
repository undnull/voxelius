/*
 * texture.hh
 * Created: 2021-01-19, 14:54:44.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_TEXTURE_HH
#define VOXELIUS_GL_TEXTURE_HH 1
#include <voxelius/gl/resource.hh>
#include <voxelius/types.hh>

namespace gl
{
    class Texture final : public Resource {
    public:
        Texture();
        ~Texture();

        void create() override;
        void release() override;
        bool is_good() const override;

        void set_repeat(bool enable);
        void set_filter(bool enable);

        template<typename T>
        void load_rgba(int width, int height, const void *data);

        void bind(unsigned int unit) const;

        inline constexpr unsigned int get_texture() const
        {
            return texture;
        }

    private:
        unsigned int texture;
    };
}

#endif
