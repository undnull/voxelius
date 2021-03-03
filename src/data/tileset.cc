/*
 * tileset.cc
 * Created: 2021-03-03, 20:46:34.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <data/tileset.hh>
#include <util/format.hh>
#include <util/fs.hh>
#include <util/logger.hh>
#include <stb_image.h>
#include <nlohmann/json.hpp>

namespace data
{
TileSet::TileSet()
{
    default_tile.top = 1.0f;
    default_tile.left = 0.0f;
    default_tile.bottom = 0.0f;
    default_tile.right = 1.0f;
}

bool TileSet::load(const char *filename)
{
    const std::string source = util::readTextFile(filename);
    if(source.empty()) {
        util::log("fs: %s is empty!", filename);
        return false;
    }

    try {
        const auto json = nlohmann::json::parse(source);

        const auto json_path = json.find("path");
        if(json_path == json.cend()) {
            util::log("json: property 'path' is required but non-existent");
            return false;
        }

        const std::string val_path = json_path->get<std::string>();

        // NTC(0, 0) = (0.0; 0.0)
        stbi_set_flip_vertically_on_load(0);

        int width, height, comp;
        stbi_uc *pixels = stbi_load(val_path.c_str(), &width, &height, &comp, STBI_rgb_alpha);
        if(!pixels) {
            util::log("fs: can't read %s (%s)", val_path.c_str(), stbi_failure_reason());
            return false;
        }

        texture.init(width, height, GL_RGBA16F);
        texture.write(width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        texture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        texture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        const auto json_filter = json.find("filter");
        if(json_filter != json.cend() && json_filter->get<bool>()) {
            texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else {
            texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        const auto json_tiles = json.find("tiles");
        if(json_tiles == json.cend()) {
            util::log("json: property 'tiles' is required but non-existent");
            return false;
        }

        const float width_f = static_cast<float>(width);
        const float height_f = static_cast<float>(height);

        for(auto it = json_tiles->begin(); it != json_tiles->end(); it++) {
            tile t;

            const auto json_x0 = it->find("x0");
            if(json_x0 != it->cend())
                t.left = json_x0->get<float>() / width_f;
            
            const auto json_y0 = it->find("y0");
            if(json_y0 != it->cend())
                t.top = json_y0->get<float>() / height_f;

            const auto json_x1 = it->find("x1");
            if(json_x1 != it->cend())
                t.right = json_x1->get<float>() / width_f;
            
            const auto json_y1 = it->find("y1");
            if(json_y1 != it->cend())
                t.bottom = json_y1->get<float>() / height_f;
            
            tiles.push_back(t);
        }

        return true;
    }
    catch(std::exception &e) {
        util::log("json: %s", e.what());
        return false;
    }
}
} // namespace data
