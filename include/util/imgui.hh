/*
 * imgui.hh
 * Created: 2021-03-06, 20:42:29.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>
#include <imgui.h>
#include <imgui_stdlib.h>

namespace util
{
inline const ImTextureID getTextureID(unsigned int id)
{
    return reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(id));
}

inline const float2_t getVec2(const ImVec2 &v)
{
    return float2_t(v.x, v.y);
}

inline const ImVec2 getVec2(const float2_t &v)
{
    return ImVec2(v.x, v.y);
}

inline const float4_t getVec4(const ImVec4 &v)
{
    return float4_t(v.x, v.y, v.z, v.w);
}

inline const ImVec4 getVec4(const float4_t &v)
{
    return ImVec4(v.x, v.y, v.z, v.w);
}
} // namespace util
