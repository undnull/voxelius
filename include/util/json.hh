/*
 * json.hh
 * Created: 2021-03-05, 12:38:20.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>
#include <util/format.hh>

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace util
{
template<glm::length_t L>
inline const glm::vec<L, float, glm::packed_highp> jsonToFloat(const json &j)
{
    glm::vec<L, float, glm::packed_highp> v;
    if(j.is_array()) {
        glm::length_t index = 0;
        for(const auto &it : j.items()) {
            if(index >= L)
                break;
            v[index++] = it.value().get<float>();
        }
    }
    return v;
}

inline const json::const_iterator jsonRequire(const json &j, const char *property)
{
    const json::const_iterator it = j.find(property);
    if(it == j.cend())
        throw std::runtime_error(util::format("property \"%s\" is required but non-existent", property));
    return it;
}
} // namespace util
