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

typedef uint_least8_t uint8;
typedef uint_least16_t uint16;
typedef uint_least32_t uint32;
typedef uint_least64_t uint64;

typedef int_least8_t int8;
typedef int_least16_t int16;
typedef int_least32_t int32;
typedef int_least64_t int64;

typedef glm::mat<4, 4, float, glm::packed_highp> float4x4;

typedef glm::vec<2, float, glm::packed_highp> float2;
typedef glm::vec<3, float, glm::packed_highp> float3;
typedef glm::vec<4, float, glm::packed_highp> float4;

#endif
