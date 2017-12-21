#include "system__view.h"

#include <SDL.h>

#include "scene.h"
#include "id_manager.h"
#include "scene_manager.h"
#include "system_manager.h"
#include "component__graphics_interface.h"
#include "renderable.h"
#include "atexture.h"
#include "subsystem_render.h"
#include "resource_manager.h"
#include "control_sheduler.h"
#include "player_controller.h"
#include "component__transform.h"

bool ViewSystem::init(RenderSubsystem& rendSubsys,
                      ResourceManager& resManager,
                      SystemManager& sysManager, 
                      SceneManager& sceneManager)
{
    m_resManager = &resManager;
    m_rendSubsystem = &rendSubsys;
    m_sceneManager = &sceneManager;
    m_sysManager = &sysManager;

    m_camera = new Camera({ 0, 0 }, { 1120, 660 });
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
        m_registered.insert(std::make_pair(actor.getID(), &actor));
        return true;
    }
    return false;
}

void ViewSystem::unreg(ActorID id)
{
    m_registered.erase(id);
}

void ViewSystem::update()
{
    m_camera->focus(*m_sysManager->m_controlSheduler->m_plController->getPossessed().begin()->second);

    auto& scene = *m_sceneManager->getScene();
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
    /*auto tiles = scene.getTilesIn(center.x - 10, center.y - 8, center.x + 10, center.y + 8);
    for (auto& pair : tiles)
    {
        auto dst = m_camera->transformToSDLRect({ pair.first.y, pair.first.x, 64, 64 });
        m_rendSubsystem->render(pair.second->getView(), dst);
    }*/
    std::map<unsigned, std::vector<Actor*>> layers;
    for (auto& pair : m_registered)
    {
        auto coord = pair.second->getCoord();
        if (coord.x >= center.x - 10 &&
            coord.x <= center.x + 10 &&
            coord.y >= center.y - 8 &&
            coord.y <= center.y + 8)
        {
            auto graphicsComp = pair.second->getComponent<GraphicsInterfaceComponent>();
            if (layers.find(graphicsComp->getLayer()) == layers.end())
            {
                layers[graphicsComp->getLayer()] = { pair.second };
            }
            else
            {
                layers[graphicsComp->getLayer()].push_back(pair.second);
            }
        }
    }
    for (auto layer : layers)
    {
        for (auto actor : layer.second)
        {
            auto coord = actor->getCoord();
            
            auto graphicsComponent = actor->getComponent<GraphicsInterfaceComponent>();
            auto atexture = m_resManager->get<Renderable>(graphicsComponent->get())->getTexture();
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
            auto sdlcenter = SDL_Point{ m_camera->getCenter().x , m_camera->getCenter().y };
            SDL_RenderCopyEx(m_rendSubsystem->getRenderer(), texture, &srcRect, &dstRect, m_camera->getRotation(), &sdlcenter, SDL_FLIP_NONE);
        }
    }
    //for (auto& pair : m_registered)
    //{
    //    auto coord = pair.second->getCoord();
    //    if (coord.x >= center.x - 10 &&
    //        coord.x <= center.x + 10 &&
    //        coord.y >= center.y - 8 &&
    //        coord.y <= center.y + 8)
    //    {
    //        auto graphicsComponent = pair.second->getComponent<GraphicsInterfaceComponent>();
    //        auto atexture = m_resManager->get<Renderable>(graphicsComponent->get())->getTexture();
    //        auto w = atexture->getWidth();
    //        auto h = atexture->getHeight();
    //        auto texture = atexture->getSDLTexture();
    //        auto srcRect = atexture->getSrcRect();
    //        auto dstRect = m_camera->transformToSDLRect({ coord.x, coord.y, w, h });
    //        auto transformComp = pair.second->getComponent<TransformComponent>();
    //        if (transformComp)
    //        {
    //            dstRect.x += transformComp->get().m_shift.x;
    //            dstRect.y += transformComp->get().m_shift.y;
    //        }
    //        // attach actor images to the bottom of the tile
    //        dstRect.x += 64 - w;
    //        dstRect.y += 64 - h;
    //        auto sdlcenter = SDL_Point{ m_camera->getCenter().x , m_camera->getCenter().y };
    //        SDL_RenderCopyEx(m_rendSubsystem->getRenderer(), texture, &srcRect, &dstRect, m_camera->getRotation(), &sdlcenter, SDL_FLIP_NONE);
    //    }
    //}
}

const Camera& ViewSystem::getCamera() const
{
    return *m_camera;
}

