/*
 * types.hh
 * Created: 2021-01-16, 15:28:51.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_TYPES_HH
#define VOXELIUS_TYPES_HH 1
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stddef.h>
#include <stdint.h>

typedef glm::mat<4, 4, float, glm::packed_highp> mat4x4_t;

typedef glm::vec<2, float, glm::packed_highp> vec2_t;
typedef glm::vec<3, float, glm::packed_highp> vec3_t;
typedef glm::vec<4, float, glm::packed_highp> vec4_t;

typedef glm::qua<float, glm::packed_highp> quat_t;

typedef glm::vec<3, float, glm::packed_highp> dcoord_t;
typedef glm::vec<3, int64_t, glm::packed_highp> icoord_t;
typedef glm::vec<3, uint8_t, glm::packed_highp> ucoord_t;

typedef uint8_t voxel_t;

#endif
