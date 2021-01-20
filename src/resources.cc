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
        const size_t hash;
        const std::string path;
        std::shared_ptr<T> ptr = nullptr;
    };

    template<typename T>
    using resource_list = std::vector<resource<T>>;

    static resource_list<gl::Program> programs;
    static resource_list<gl::Texture> textures;

    template<typename T>
    static inline const size_t cleanup_list(resource_list<T> &list)
    {
        size_t count = 0;
        for(const resource<T> &res : list) {
            if(res.ptr.use_count() > 1) {
                logger::dlog("resources: warning: resource %s (%zX) is still referenced", res.path.c_str(), res.hash);
                count++;
            }
        }
        list.clear();
        return count;
    }

    template<typename T>
    static inline std::shared_ptr<T> try_get_resource(resource_list<T> &list, const char *id)
    {
        const size_t hash = std::hash<const char *>{}(id);
        for(resource<T> &res : list) {
            if(res.hash == hash)
                return res.ptr;
        }
        return nullptr;
    }

    void init()
    {
        programs.clear();
        textures.clear();
    }

    void cleanup()
    {
        size_t count = 0;
        count += cleanup_list<gl::Program>(programs);
        count += cleanup_list<gl::Texture>(textures);
        logger::dlog("resources: found %zu still referenced resources", count);
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
            logger::dlog("resources: error: stb: %s (%s)", stbi_failure_reason(), path);
            return nullptr;
        }

        resource<gl::Texture> res = { hash, path, std::make_shared<gl::Texture>() };
        res.ptr->load_rgba<uint8_t>(width, height, pixels);

        textures.push_back(res);
        return res.ptr;
    }
}
