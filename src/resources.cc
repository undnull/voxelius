/*
 * resources.cc
 * Created: 2021-01-20, 21:18:37.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/gl/program.hh>
#include <voxelius/gl/texture.hh>
#include <voxelius/util/file.hh>
#include <voxelius/logger.hh>
#include <voxelius/resources.hh>
#include <stb_image.h>
#include <vector>

namespace resources
{
    template<typename T>
    struct resource final {
        size_t hash;
        std::string path;
        size_t use_count;
        T *ptr;
    };

    template<typename T>
    using resource_list = std::vector<resource<T>>;

    static resource_list<gl::Program> programs;
    static resource_list<gl::Texture> textures;

    template<typename T>
    static inline size_t cleanup(resource_list<T> &list)
    {
        size_t count = 0, idx = 0;
        for(const resource<T> &res : list) {
            if(res.use_count > 0) {
                count++;
                continue;
            }
            list.erase(list.cbegin() + idx++);
        }
        return count;
    }

    template<typename T>
    static inline T * get(size_t hash, resource_list<T> &list)
    {
        if(hash != 0) {
            for(resource<T> &res : list) {
                if(res.hash == hash)
                    return res.ptr;
            }
        }
        return nullptr;
    }

    template<typename T>
    static inline void release(T *ptr, resource_list<T> &list)
    {
        for(resource<T> &res : list) {
            if(res.ptr == ptr && res.use_count > 0) {
                res.use_count--;
                return;
            }
        }
    }

    void cleanup()
    {
        size_t count = 0;
        count += cleanup<gl::Program>(programs);
        count += cleanup<gl::Texture>(textures);
        logger::dlog("resources: %zu resources are still used", count);
    }

    template<>
    size_t load<gl::Program>(const char *path)
    {
        const size_t hash = std::hash<const char *>{}(path);

        // try to find an existing program
        for(const resource<gl::Program> &res : programs) {
            if(res.hash == hash)
                return hash;
        }

        std::string filename;
        std::vector<uint8_t> vspv, fspv;

        filename = util::format("./shaders/%s.vspv", path);
        vspv = util::file_read_bin(filename.c_str());
        if(vspv.empty()) {
            logger::dlog("resources: error: %s contains no data", filename.c_str());
            return 0;
        }

        filename = util::format("./shaders/%s.fspv", path);
        fspv = util::file_read_bin(filename.c_str());
        if(fspv.empty()) {
            logger::dlog("resources: error: %s contains no data", filename.c_str());
            return 0;
        }

        gl::VertexShader vert;
        gl::FragmentShader frag;

        vert.set_binary(vspv.data(), vspv.size());
        if(!vert.specialize("main")) {
            logger::dlog("opengl %s", vert.get_info_log());
            return 0;
        }

        frag.set_binary(fspv.data(), fspv.size());
        if(!frag.specialize("main")) {
            logger::dlog("opengl: %s", frag.get_info_log());
            return 0;
        }

        resource<gl::Program> res = { hash, path, 0, new gl::Program() };
        res.ptr->attach(vert);
        res.ptr->attach(frag);
        if(!res.ptr->link()) {
            logger::dlog("opengl %s", res.ptr->get_info_log());
            delete res.ptr;
            return 0;
        }

        frag.release();
        vert.release();

        programs.push_back(res);
        return hash;
    }

    template<>
    gl::Program * get(size_t hash)
    {
        return get<gl::Program>(hash, programs);
    }

    template<>
    void release(gl::Program *ptr)
    {
        release<gl::Program>(ptr, programs);
    }

    template<>
    size_t load<gl::Texture>(const char *path)
    {
        const size_t hash = std::hash<const char *>{}(path);

        // try to find an existing texture
        for(const resource<gl::Texture> &res : textures) {
            if(res.hash == hash)
                return hash;
        }

        const std::string filename = util::format("./textures/%s", path);
        int width, height, channels;
        stbi_uc *pixels;

        stbi_set_flip_vertically_on_load(1);
        pixels = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        if(!pixels) {
            logger::dlog("resources: error: %s (%s)", stbi_failure_reason(), filename.c_str());
            return 0;
        }

        resource<gl::Texture> res = { hash, path, 0, new gl::Texture() };
        res.ptr->load_rgba<uint8_t>(width, height, pixels);

        textures.push_back(res);

        stbi_image_free(pixels);
        
        return hash;
    }

    template<>
    gl::Texture * get(size_t hash)
    {
        return get<gl::Texture>(hash, textures);
    }

    template<>
    void release(gl::Texture *ptr)
    {
        release<gl::Texture>(ptr, textures);
    }
}
