#include "camera.h"

#include "actor.h"

Camera::Camera() :
    m_focus(nullptr),
    m_transformComp(nullptr),
    m_center(0, 0),
    m_size(0, 0),
    m_viewport(0, 0, 1, 1),
    m_rotation(0)
{}

Camera::Camera(Vec2i center, Vec2i size) :
    m_focus(nullptr), 
    m_transformComp(nullptr),
    m_center(center),
    m_size(size),
    m_viewport(0, 0, 1, 1),
    m_rotation(0)
{
}

void Camera::setCenter(Vec2i center)
{
    m_center = center;
}

void Camera::setSize(Vec2i size)
{
    m_size = size;
}

void Camera::setRotation(float rotation)
{
    m_rotation = rotation;
}

void Camera::setViewport(IRect viewport)
{
    m_viewport = viewport;
}

const Vec2i& Camera::getCenter() const
{
    return (m_focus != nullptr) ? *m_focus : m_center;
}

const Vec2i& Camera::getSize() const
{
    return m_size;
}

const float& Camera::getRotation() const
{
    return m_rotation;
}

const IRect& Camera::getViewport() const
{
    return m_viewport;
}

const Vec2i* Camera::getFocus() const
{
    return m_focus;
}

SDL_Rect Camera::transformToSDLRect(IRect rect) const
{
    auto& center = getCenter();
    auto result = SDL_Rect{
        static_cast<int>(m_viewport.x + tileWidth * static_cast<int>((rect.x - center.x) * m_viewport.w / m_size.x) + 0.5 * m_viewport.w),
        static_cast<int>(m_viewport.y + tileHeight * static_cast<int>((rect.y - center.y) * m_viewport.h / m_size.y) + 0.5 * m_viewport.h),
        static_cast<int>(1. * rect.w * m_viewport.w / m_size.x),
        static_cast<int>(1. * rect.h * m_viewport.h / m_size.y)
    };
    if (m_transformComp)
    {
        result.x -= m_transformComp->get().m_shift.x;
        result.y -= m_transformComp->get().m_shift.y;
    }
    return result;
}

void Camera::focus(Actor& actor)
{
    m_focus = &actor.getCoord();
    m_transformComp = actor.getComponent<TransformComponent>();
}

void Camera::defocus()
{
    m_focus = nullptr;
    m_transformComp = nullptr;
}

void Camera::rotate(float rotation)
{
    setRotation(m_rotation + rotation);
}

void Camera::zoom(float factor)
{
    setSize({ 
        static_cast<int>(m_size.x * factor), 
        static_cast<int>(m_size.y * factor)
    });
}