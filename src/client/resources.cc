/*
 * resources.cc
 * Created: 2021-01-20, 21:18:37.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/client/gl/program.hh>
#include <voxelius/client/gl/texture.hh>
#include <voxelius/client/resources.hh>
#include <voxelius/logger.hh>
#include <voxelius/util/file.hh>

#include <stb_image.h>

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

static resource_list<gl::Program> programs;
static resource_list<gl::Texture> textures;

void cleanup(bool cached)
{
    size_t count = 0;
    count += cleanup<gl::Program>(programs, cached);
    count += cleanup<gl::Texture>(textures, cached);
    logger::dlog("resources: cleaned up %zu resources", count);
}

template<>
hash_t load<gl::Program>(const char *path, bool cached)
{
    const size_t hash = std::hash<const char *> {}(path);

    for(const resource<gl::Program> &res : programs) {
        if(res.hash == hash)
            return hash;
    }

    std::string filename;
    std::vector<uint8_t> vspv, fspv;

    filename = util::format("./shaders/%s.vspv", path);
    vspv = util::readBinaryFile(filename.c_str());

    if(vspv.empty()) {
        logger::dlog("resources: error: %s contains no data", filename.c_str());
        return 0;
    }

    filename = util::format("./shaders/%s.fspv", path);
    fspv = util::readBinaryFile(filename.c_str());

    if(fspv.empty()) {
        logger::dlog("resources: error: %s contains no data", filename.c_str());
        return 0;
    }

    gl::VertexShader vs;
    gl::FragmentShader fs;

    vs.setBinary(vspv.data(), vspv.size());
    if(!vs.specialize("main")) {
        logger::dlog("opengl: %s", vs.get_info_log());
        return 0;
    }

    fs.setBinary(fspv.data(), fspv.size());
    if(!fs.specialize("main")) {
        logger::dlog("opengl: %s", fs.get_info_log());
        return 0;
    }

    resource<gl::Program> res = { hash, 0, cached, path, new gl::Program() };

    res.ptr->attach(vs);
    res.ptr->attach(fs);

    if(!res.ptr->link()) {
        logger::dlog("opengl: %s", res.ptr->getInfoLog());
        delete res.ptr;
        return 0;
    }

    fs.release();
    vs.release();

    programs.push_back(res);

    return hash;
}

template<>
gl::Program *acquire(hash_t hash)
{
    return acquire(programs, hash);
}

template<>
void release(gl::Program *obj)
{
    release(programs, obj);
}

template<>
hash_t load<gl::Texture>(const char *path, bool cached)
{
    const size_t hash = std::hash<const char *> {}(path);

    for(const resource<gl::Texture> &res : textures) {
        if(res.hash == hash)
            return hash;
    }

    const std::string filename = util::format("./textures/%s", path);

    stbi_set_flip_vertically_on_load(1);

    int width, height, comp;
    stbi_uc *pixels = stbi_load(filename.c_str(), &width, &height, &comp, STBI_rgb_alpha);

    if(!pixels) {
        logger::dlog("stb: error: %s (%s)", stbi_failure_reason(), filename.c_str());
        return 0;
    }

    resource<gl::Texture> res = { hash, 0, cached, path, new gl::Texture };

    res.ptr->loadRGBA<uint8_t>(width, height, pixels);

    stbi_image_free(pixels);

    textures.push_back(res);

    return hash;
}

template<>
gl::Texture *acquire(hash_t hash)
{
    return acquire(textures, hash);
}

template<>
void release(gl::Texture *obj)
{
    release(textures, obj);
}
} // namespace resources
