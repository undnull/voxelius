/*
 * object.hh
 * Created: 2021-01-19, 11:36:59.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once

namespace gl
{
class Object {
public:
    virtual void create() = 0;
    virtual void release() = 0;
    virtual bool isGood() const = 0;
};
} // namespace gl
