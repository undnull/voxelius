/*
 * resources.hh
 * Created: 2021-01-20, 20:34:25.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_RESOURCES_HH
#define VOXELIUS_RESOURCES_HH 1
#include <voxelius/types.hh>

namespace resources
{
    void cleanup();

    template<typename T>
    size_t load(const char *path);

    template<typename T>
    T * get(size_t hash);

    template<typename T>
    void release(T *ptr);

    template<typename T>
    static inline T * load_and_get(const char *path)
    {
        return get<T>(load<T>(path));
    }
}

#endif
