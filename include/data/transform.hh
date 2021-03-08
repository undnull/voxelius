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

    void setOrigin(const float2_t &origin);
    void setPosition(const float2_t &position);
    void setRotation(float rotation);
    void setScale(float scale_v);

    void move(const float2_t &velocity);
    void rotate(float angle);
    void scale(float f);

    const float2_t &getOrigin() const;
    const float2_t &getPosition() const;
    float getRotation() const;
    float getScale() const;

    void update();

    const float4x4_t &getMatrix() const;

private:
    float2_t origin;
    float2_t position;
    float rotation;
    float scale_v;

    float4x4_t matrix;
};

inline Transform::Transform()
{
    origin = float2_t(0.0f, 0.0f);
    position = float2_t(0.0f, 0.0f);
    rotation = 0.0f;
    scale_v = 1.0f;

    matrix = float4x4_t(1.0f);
    update();
}

inline void Transform::setOrigin(const float2_t &origin)
{
    this->origin = origin;
    update();
}

inline void Transform::setPosition(const float2_t &position)
{
    this->position = position;
    update();
}

inline void Transform::setRotation(float rotation)
{
    this->rotation = rotation;
    update();
}

inline void Transform::setScale(float scale_v)
{
    this->scale_v = scale_v;
    update();
}

inline void Transform::move(const float2_t &velocity)
{
    position += velocity;
    update();
}

inline void Transform::rotate(float angle)
{
    rotation += angle;
    rotation = fmodf(rotation, 360.0f);
    update();
}

inline void Transform::scale(float f)
{
    scale_v *= f;
    update();
}

inline const float2_t &Transform::getOrigin() const
{
    return origin;
}

inline const float2_t &Transform::getPosition() const
{
    return position;
}

inline float Transform::getRotation() const
{
    return rotation;
}

inline float Transform::getScale() const
{
    return scale_v;
}

inline void Transform::update()
{
    matrix = float4x4_t(1.0f);
    matrix = glm::translate(matrix, float3_t(position, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation), float3_t(0.0f, 0.0f, 1.0f));
    matrix = glm::translate(matrix, float3_t(-origin, 0.0f));
    matrix = glm::scale(matrix, float3_t(scale_v, scale_v, 1.0f));
}

inline const float4x4_t &Transform::getMatrix() const
{
    return matrix;
}
} // namespace data
