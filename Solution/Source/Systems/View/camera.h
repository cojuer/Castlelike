#pragma once

#include <SDL.h>

#include "rect.h"
#include "vec2.h"

#include "component__transform.h"

class Actor;

class Camera
{
public:
    static constexpr int tileWidth = 64;
    static constexpr int tileHeight = 64;

    Camera();
    Camera(Vec2i center, Vec2i size);

    void setCenter(Vec2i center);
    void setSize(Vec2i size);
    void setRotation(float rotation);
    void setViewport(IRect viewport);

    const Vec2i& getCenter() const;
    const Vec2i& getSize() const;
    const float& getRotation() const;
    const IRect& getViewport() const;
    const Vec2i* getFocus() const;

    SDL_Rect transformToSDLRect(IRect rect) const;

    void focus(Actor& actor);
    void defocus();

    void rotate(float rotation);
    void zoom(float factor);

private:
    const Vec2i* m_focus;
    const TransformComponent* m_transformComp;
    Vec2i    m_center;
    Vec2i    m_size;
    IRect    m_viewport;
    float    m_rotation;
};
