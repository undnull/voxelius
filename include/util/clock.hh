/*
 * clock.hh
 * Created: 2021-03-02, 22:55:43.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once

namespace util
{
class Clock {
public:
    Clock();

    float getTime() const;
    float reset();

private:
    float start;
};
} // namespace util
