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
#include <stddef.h>
#include <stdint.h>

typedef glm::mat<4, 4, double, glm::packed_highp> mat4x4_t;

typedef glm::vec<2, double, glm::packed_highp> vec2_t;
typedef glm::vec<3, double, glm::packed_highp> vec3_t;
typedef glm::vec<4, double, glm::packed_highp> vec4_t;

// uint8_t is temporary for now and just describes a color.
// when I get to some more complex voxels (maybe textured)
// this must be changed to uint16_t...
typedef uint8_t voxel_t;
typedef voxel_t * chunk_t;

#endif
