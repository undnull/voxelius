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
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <utility>

typedef glm::mat<4, 4, float, glm::packed_highp> float4x4_t;

typedef glm::vec<2, float, glm::packed_highp> float2_t;
typedef glm::vec<3, float, glm::packed_highp> float3_t;
typedef glm::vec<4, float, glm::packed_highp> float4_t;

typedef glm::qua<float, glm::packed_highp> quat_t;
