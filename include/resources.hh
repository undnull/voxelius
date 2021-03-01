/*
 * resources.hh
 * Created: 2021-01-20, 20:34:25.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace resources
{
void cleanup(bool cached = false);

template<typename T>
hash_t load(const char *path, bool cached = false);

template<typename T>
T *acquire(hash_t hash);

template<typename T>
void release(T *obj);

template<typename T>
T *acquire(const char *path)
{
    return acquire<T>(load<T>(path, false));
}
} // namespace resources
