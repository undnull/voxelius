/*
 * transform.hh
 * Created: 2021-03-07, 22:54:23.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace data
{
class Transform final {
public:
    Transform();

    void setPosition(const float2_t &position);
    void setRotation(float rotation);
    void setScale(const float2_t &scale);
    void setScale(float scale);

    void move(const float2_t &delta);
    void rotate(float delta);

    const float2_t &getPosition() const;
    float getRotation() const;
    const float2_t &getScale() const;

    const float4x4_t &getMatrix();

private:
    float2_t position;
    float rotation;
    float2_t scale;

    float4x4_t matrix;
    bool needs_update;
};

inline Transform::Transform()
{
    position = float2_t(0.0f, 0.0f);
    rotation = 0.0f;
    scale = float2_t(1.0f, 1.0f);

    matrix = float4x4_t(1.0f);
    needs_update = true;
}

inline void Transform::setPosition(const float2_t &position)
{
    this->position = position;
    needs_update = true;
}

inline void Transform::setRotation(float rotation)
{
    this->rotation = rotation;
    needs_update = true;
}

inline void Transform::setScale(const float2_t &scale)
{
    this->scale = scale;
    needs_update = true;
}

inline void Transform::setScale(float scale)
{
    this->scale = float2_t(scale, scale);
    needs_update = true;
}

inline void Transform::move(const float2_t &delta)
{
    position += delta;
    needs_update = true;
}

inline void Transform::rotate(float delta)
{
    rotation += delta;
    needs_update = true;
}

inline const float2_t &Transform::getPosition() const
{
    return position;
}

inline float Transform::getRotation() const
{
    return rotation;
}

inline const float2_t &Transform::getScale() const
{
    return scale;
}

inline const float4x4_t &Transform::getMatrix()
{
    if(needs_update) {
        matrix = float4x4_t(1.0f);
        matrix = glm::translate(matrix, float3_t(position, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotation), float3_t(0.0f, 0.0f, 1.0f));
        matrix = glm::scale(matrix, float3_t(scale, 1.0f));
        needs_update = false;
    }
    return matrix;
}
} // namespace data
