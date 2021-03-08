/*
 * view.hh
 * Created: 2021-03-08, 18:42:47.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <types.hh>

namespace data
{
class View final {
public:
    View();

    void setPosition(const float2_t &position);
    void setRotation(float rotation);
    void setZoomFactor(float zoom_v);

    void move(const float2_t &velocity);
    void rotate(float angle);
    void zoom(float f);

    const float2_t &getPosition() const;
    float getRotation() const;
    float getZoomFactor() const;

    void update();

    const float4x4_t &getMatrix() const;

private:
    float2_t position;
    float rotation;
    float zoom_v;

    float4x4_t matrix;
};

inline View::View()
{
    position = float2_t(0.0f, 0.0f);
    rotation = 0.0f;
    zoom_v = 1.0f;

    matrix = float4x4_t(1.0f);
    update();
}

inline void View::setPosition(const float2_t &position)
{
    this->position = position;
    update();
}

inline void View::setRotation(float rotation)
{
    this->rotation = rotation;
    update();
}

inline void View::setZoomFactor(float zoom_v)
{
    this->zoom_v = zoom_v;
    update();
}

inline void View::move(const float2_t &velocity)
{
    position += velocity;
    update();
}

inline void View::rotate(float angle)
{
    rotation += angle;
    update();
}

inline void View::zoom(float f)
{
    zoom_v *= f;
    update();
}

inline const float2_t &View::getPosition() const
{
    return position;
}

inline float View::getRotation() const
{
    return rotation;
}

inline float View::getZoomFactor() const
{
    return zoom_v;
}

inline void View::update()
{
    matrix = float4x4_t(1.0f);
    matrix = glm::translate(matrix, float3_t(position, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation), float3_t(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, 1.0f / float3_t(zoom_v, zoom_v, 1.0f));
}

inline const float4x4_t &View::getMatrix() const
{
    return matrix;
}
} // namespace data
