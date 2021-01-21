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
        std::shared_ptr<T> ptr;
    };

    template<typename T>
    using resource_list = std::vector<resource<T>>;

    static resource_list<gl::Program> programs;
    static resource_list<gl::Texture> textures;

    template<typename T>
    static inline const size_t release_all(resource_list<T> &list)
    {
        size_t count = 0;
        for(const resource<T> &res : list) {
            if(res.ptr.use_count() > 1) {
                logger::dlog("resources: warning: %s (%zu) is still used", res.path.c_str(), res.hash);
                count++;
            }
        }

        return count;
    }

    template<typename T>
    static inline const size_t release_unused(resource_list<T> &list)
    {
        size_t count = 0, pos = 0;
        for(const resource<T> &res : list) {
            if(res.ptr.use_count() == 1) {
                list.erase(list.cbegin() + pos);
                count++;
            }

            pos++;
        }
        
        return count;
    }

    void init()
    {
        programs.clear();
        textures.clear();
    }

    void release_all()
    {
        size_t count = 0;
        count += release_all<gl::Program>(programs);
        count += release_all<gl::Texture>(textures);
        logger::dlog("resources: found %zu still used resources", count);
    }

    void release_unused()
    {
        size_t count = 0;
        count += release_unused<gl::Program>(programs);
        count += release_unused<gl::Texture>(textures);
        logger::dlog("resources: found and released %zu unused resources", count);
    }

    template<>
    std::shared_ptr<gl::Program> get_resource(const char *path)
    {
        const size_t hash = std::hash<const char *>{}(path);

        // try to find an existing program
        for(resource<gl::Program> &res : programs) {
            if(res.hash == hash)
                return res.ptr;
        }

        std::string filename;
        std::vector<uint8_t> vspv, fspv;

        filename = util::format("./shaders/%s.vspv", path);
        vspv = util::file_read_bin(filename.c_str());
        if(vspv.empty()) {
            logger::dlog("resources: error: %s contains no data", filename.c_str());
            return nullptr;
        }

        filename = util::format("./shaders/%s.fspv", path);
        fspv = util::file_read_bin(filename.c_str());
        if(fspv.empty()) {
            logger::dlog("resources: error: %s contains no data", filename.c_str());
            return nullptr;
        }

        gl::VertexShader vert;
        gl::FragmentShader frag;

        vert.set_binary(vspv.data(), vspv.size());
        if(!vert.specialize("main")) {
            logger::dlog("opengl %s", vert.get_info_log());
            return nullptr;
        }

        frag.set_binary(fspv.data(), fspv.size());
        if(!frag.specialize("main")) {
            logger::dlog("opengl: %s", frag.get_info_log());
            return nullptr;
        }

        resource<gl::Program> res = { hash, path, std::make_shared<gl::Program>() };
        
        res.ptr->attach(vert);
        res.ptr->attach(frag);
        if(!res.ptr->link()) {
            logger::dlog("opengl: %s", res.ptr->get_info_log());
            return nullptr;
        }

        frag.release();
        vert.release();

        programs.push_back(res);
        return res.ptr;
    }

    template<>
    std::shared_ptr<gl::Texture> get_resource(const char *path)
    {
        const size_t hash = std::hash<const char *>{}(path);

        // try to find an existing texture
        for(resource<gl::Texture> &res : textures) {
            if(res.hash == hash)
                return res.ptr;
        }

        stbi_set_flip_vertically_on_load(1);

        const std::string filename = util::format("./textures/%s", path);
        int width, height, comp;
        stbi_uc *pixels = stbi_load(filename.c_str(), &width, &height, &comp, STBI_rgb_alpha);
        if(!pixels) {
            logger::dlog("resources: error: %s (%s)", stbi_failure_reason(), path);
            return nullptr;
        }

        resource<gl::Texture> res = { hash, path, std::make_shared<gl::Texture>() };
        res.ptr->load_rgba<uint8_t>(width, height, pixels);

        textures.push_back(res);
        return res.ptr;
    }
}
