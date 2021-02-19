/*
 * vao.hh
 * Created: 2021-01-19, 11:56:58.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_VAO_HH
#define VOXELIUS_GL_VAO_HH 1
#include <voxelius/gl/buffer.hh>

namespace gl
{
class VAO final : public Object {
public:
    VAO();
    ~VAO();

    void create() override;
    void release() override;
    bool isGood() const override;

    void bindVBO(const Buffer &buffer, unsigned int binding_index, size_t offset, size_t stride);
    void bindEBO(const Buffer &buffer);

    void enableAttrib(unsigned int attrib_index);
    template<typename T>
    void setAttribFormat(unsigned int attrib_index, size_t count, bool normalized);
    void setAttribBinding(unsigned int attrib_index, unsigned int binding_index);

    inline constexpr unsigned int getVAO() const
    {
        return vao;
    }

private:
    unsigned int vao;
};
} // namespace gl

#endif
