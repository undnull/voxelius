/*
 * types.hh
 * Created: 2021-01-16, 15:28:51.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <sstream>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using float4x4_t = glm::mat<4, 4, float, glm::packed_highp>;

using float2_t = glm::vec<2, float, glm::packed_highp>;
using float3_t = glm::vec<3, float, glm::packed_highp>;
using float4_t = glm::vec<4, float, glm::packed_highp>;
