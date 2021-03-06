/*
 * map.cc
 * Created: 2021-03-05, 12:36:19.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/map.hh>
#include <data/vertex.hh>
#include <util/format.hh>
#include <util/fs.hh>
#include <util/json.hh>
#include <util/logger.hh>

#include <stb_image.h>

namespace data
{
bool Map::loadFromFile(const fs::path &path)
{
    layers.clear();

    if(!fs::exists(path)) {
        util::log("map: file %s doesn't exist", path.string().c_str());
        return false;
    }

    try {
        const json &j = json::parse(util::readTextFile(path));

        const auto j_layers = util::jsonRequire(j, "layers");
        for(const auto &it_layer : j_layers->items()) {
            const auto j_layer = it_layer.value();

            const auto layer_vertex = util::jsonRequire(j_layer, "vertex");
            const auto layer_fragment = util::jsonRequire(j_layer, "fragment");
            const auto layer_textures = util::jsonRequire(j_layer, "textures");
            const auto layer_geometry = util::jsonRequire(j_layer, "geometry");

            layer l;

            const std::string s_vertex = layer_vertex->get<std::string>();
            if(!fs::exists(s_vertex)) {
                util::log("map: file %s doesn't exist", s_vertex.c_str());
                return false;
            }

            const std::vector<uint8_t> vspv = util::readBinaryFile(s_vertex);
            if(!l.vertex.link(vspv.data(), vspv.size())) {
                util::log("map: %s", l.vertex.getInfoLog());
                return false;
            }

            const std::string s_fragment = layer_fragment->get<std::string>();
            if(!fs::exists(s_fragment)) {
                util::log("map: file %s doesn't exist", s_fragment.c_str());
                return false;
            }

            const std::vector<uint8_t> fspv = util::readBinaryFile(s_fragment);
            if(!l.fragment.link(fspv.data(), fspv.size())) {
                util::log("map: %s", l.fragment.getInfoLog());
                return false;
            }

            l.pipeline.stage(l.vertex);
            l.pipeline.stage(l.fragment);

            for(const auto &it : layer_textures->items()) {
                const auto texture = it.value();

                const auto texture_path = util::jsonRequire(texture, "path");
                const auto texture_filter = texture.find("filter");
                const auto texture_repeat = texture.find("repeat");
                const auto texture_unit = util::jsonRequire(texture, "unit");

                const std::string s_path = texture_path->get<std::string>();
                int width, height, comp;
                stbi_uc *pixels;

                stbi_set_flip_vertically_on_load(0);
                pixels = stbi_load(s_path.c_str(), &width, &height, &comp, STBI_rgb_alpha);
                if(!pixels) {
                    util::log("map: can't read %s (%s)", s_path.c_str(), stbi_failure_reason());
                    continue;
                }

                gfx::Texture tex;
                tex.init(width, height, GL_RGBA16F);
                tex.write(width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

                if(texture_filter != texture.cend() && texture_filter->get<bool>()) {
                    tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                } else {
                    tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                }

                if(texture_repeat != texture.cend() && texture_repeat->get<bool>()) {
                    tex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
                    tex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
                } else {
                    tex.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    tex.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                }

                l.textures[texture_unit->get<unsigned int>()] = std::move(tex);
            }

            const auto geometry_vbo = util::jsonRequire(*layer_geometry, "vbo");
            const auto geometry_ebo = util::jsonRequire(*layer_geometry, "ebo");

            std::vector<vertex> vertices;
            std::vector<unsigned int> indices;

            for(const auto &it : geometry_vbo->items()) {
                const auto vtx = it.value();

                vertex v;
                v.position = util::jsonToFloat<2>(*util::jsonRequire(vtx, "xy"));
                v.texcoord = util::jsonToFloat<2>(*util::jsonRequire(vtx, "uv"));

                vertices.push_back(v);
            }

            for(const auto &it : geometry_ebo->items())
                indices.push_back(it.value().get<unsigned int>());

            size_t vbo_size = sizeof(vertex) * vertices.size();
            size_t ebo_size = sizeof(unsigned int) * indices.size();

            l.geometry_vbo.resize(vbo_size);
            l.geometry_vbo.write(0, vertices.data(), vbo_size);

            l.geometry_ebo.resize(ebo_size);
            l.geometry_ebo.write(0, indices.data(), ebo_size);

            l.geometry_vao.bindElementBuffer(l.geometry_ebo);
            l.geometry_vao.bindVertexBuffer(l.geometry_vbo, 0, offsetof(vertex, position), sizeof(vertex));
            l.geometry_vao.bindVertexBuffer(l.geometry_vbo, 1, offsetof(vertex, texcoord), sizeof(vertex));

            l.geometry_vao.enableAttribute(0);
            l.geometry_vao.enableAttribute(1);

            l.geometry_vao.setAttributeFormat<float>(0, 2, false);
            l.geometry_vao.setAttributeFormat<float>(1, 2, false);

            l.geometry_vao.setAttributeBinding(0, 0);
            l.geometry_vao.setAttributeBinding(1, 1);

            l.geometry_count = indices.size();

            // fixme: should I add a move constructor
            // or everything will be automatically moved?
            layers.push_back(std::move(l));
        }

        return true;
    } catch(const std::exception &e) {
        util::log("map: %s", e.what());
        return false;
    }
}

} // namespace data
