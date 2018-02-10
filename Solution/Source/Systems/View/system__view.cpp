#include "system__view.h"

#include <SDL.h>

#include "subsystem__render.h"
#include "system__actor_id.h"
#include "system__resource.h"
#include "system__scene.h"

#include "component__graphics_interface.h"
#include "component__transform.h"
#include "scene.h"
#include "renderable.h"
#include "atexture.h"

bool ViewSystem::init(RenderSubsystem& rendSubsys,
                      ResourceSystem& resSystem,
                      SceneSystem& sceneSystem)
{
    m_resSystem = &resSystem;
    m_rendSubsystem = &rendSubsys;
    m_sceneSystem = &sceneSystem;

    m_camera.reset(new Camera({ 0, 0 }, { 1120, 660 }));
    m_camera->setViewport({ 0, 0, 1120, 660 });
    auto& vport = m_camera->getViewport();
    SDL_Rect rect{ vport.x, vport.y, vport.w, vport.h };
    SDL_RenderSetViewport(m_rendSubsystem->getRenderer(), &rect);

    return true;
}

bool ViewSystem::reg(Actor& actor)
{
    auto graphicsComponent = actor.getComponent<GraphicsInterfaceComponent>();
    if (graphicsComponent)
    {
        assert(m_registered.find(actor.getID()) == m_registered.end() &&
               "ViewSystem: trying to register actor with existent ID");
        m_registered.insert(std::make_pair(actor.getID(), &actor));
        return true;
    }
    return false;
}

void ViewSystem::unreg(ActorID id)
{
    m_registered.erase(id);
}

void ViewSystem::render()
{
    m_camera->focus(*m_sceneSystem->getScene()->getHero());

    auto& scene = *m_sceneSystem->getScene();
    auto& center = m_camera->getCenter();
    for (auto y = center.y - 8 ; y <= center.y + 8; ++y)
    {
        for (auto x = center.x - 10; x <= center.x + 10; ++x)
        {
            auto dst = m_camera->transformToSDLRect({ x, y, 64, 64 });
            auto tile = scene.getTile({ x, y });
            if (tile)
            {
                m_rendSubsystem->render(tile->getView(), dst);
            }
        }
    }

    std::map<unsigned, std::vector<Actor*>> layers;
    for (auto& [id, actor] : m_registered)
    {
        auto coord = actor->getCoord();
        if (coord.x >= center.x - 10 &&
            coord.x <= center.x + 10 &&
            coord.y >= center.y - 8 &&
            coord.y <= center.y + 8)
        {
            auto graphicsComp = actor->getComponent<GraphicsInterfaceComponent>();
            if (layers.find(graphicsComp->getLayer()) == layers.end())
            {
                layers[graphicsComp->getLayer()] = { actor };
            }
            else
            {
                layers[graphicsComp->getLayer()].push_back(actor);
            }
        }
    }
    for (auto& [layer, actors] : layers)
    {
        for (auto actor : actors)
        {
            auto coord = actor->getCoord();
            
            auto graphicsComponent = actor->getComponent<GraphicsInterfaceComponent>();
            auto atexture = m_resSystem->get<Renderable>(graphicsComponent->get())->getTexture();
            auto w = atexture->getWidth();
            auto h = atexture->getHeight();
            auto texture = atexture->getSDLTexture();
            auto srcRect = atexture->getSrcRect();
            auto dstRect = m_camera->transformToSDLRect({ coord.x, coord.y, w, h });
            auto transformComp = actor->getComponent<TransformComponent>();
            if (transformComp)
            {
                dstRect.x += transformComp->get().m_shift.x;
                dstRect.y += transformComp->get().m_shift.y;
            }
            // attach actor images to the bottom of the tile
            dstRect.x += 64 - w;
            dstRect.y += 64 - h;
            SDL_Point sdlcenter{ m_camera->getCenter().x , m_camera->getCenter().y };
            SDL_RenderCopyEx(m_rendSubsystem->getRenderer(), texture, &srcRect, &dstRect, m_camera->getRotation(), &sdlcenter, SDL_FLIP_NONE);
        }
    }
}

void ViewSystem::clean()
{
    m_registered.clear();
}

const Camera& ViewSystem::getCamera() const
{
    return *m_camera;
}

