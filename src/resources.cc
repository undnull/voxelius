/*
 * resources.cc
 * Created: 2021-01-20, 21:18:37.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <logger.hh>
#include <resources.hh>

#include <vector>

namespace resources
{
template<typename T>
struct resource final {
    hash_t hash;
    size_t use_count;
    bool cached;
    std::string path;
    T *ptr;
};

template<typename T>
using resource_list = std::vector<resource<T>>;

template<typename T>
static inline size_t cleanup(resource_list<T> &list, bool cached)
{
    size_t count = 0, idx = 0;
    for(resource<T> &res : list) {
        if(res.use_count == 0 && (cached || !res.cached)) {
            delete res.ptr;
            list.erase(list.cbegin() + idx);
            count++;
        }
        idx++;
    }
    return count;
}

template<typename T>
static inline T *acquire(resource_list<T> &list, hash_t hash)
{
    for(resource<T> &res : list) {
        if(res.hash == hash) {
            res.use_count++;
            return res.ptr;
        }
    }
    return nullptr;
}

template<typename T>
static inline void release(resource_list<T> &list, T *obj)
{
    for(resource<T> &res : list) {
        if(res.ptr == obj) {
            if(!res.cached && res.use_count != 0)
                res.use_count--;
            return;
        }
    }
}

void cleanup(bool cached)
{
}
} // namespace resources
