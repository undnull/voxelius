/*
 * object.hh
 * Created: 2021-01-19, 11:36:59.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef GL_OBJECT_HH
#define GL_OBJECT_HH 1

namespace gl
{
class Object {
public:
    virtual void create() = 0;
    virtual void release() = 0;
    virtual bool isGood() const = 0;
};
} // namespace gl

#endif
