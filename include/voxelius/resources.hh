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
    void init();
    void cleanup();

    template<typename T>
    std::shared_ptr<T> get_resource(const char *path);
}

#endif
