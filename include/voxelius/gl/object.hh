/*
 * object.hh
 * Created: 2021-01-19, 11:36:59.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_GL_OBJECT_HH
#define VOXELIUS_GL_OBJECT_HH 1

namespace gl
{
    class Object {
    public:
        virtual void create() = 0;
        virtual void release() = 0;
        virtual bool is_good() const = 0;
    };
}

#endif
