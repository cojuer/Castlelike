#include "system__control.h"

#include <iostream>

#include "ai_controller.h"
#include "player_controller.h"
#include "component__action_pts.h"

bool ControlGSystem::init(InputSubsystem& inputSubsystem, SceneSystem& sceneSystem)
{
    m_aiController = new AIController();
    m_plController = new PlayerController();

    auto inited = true;
    inited = inited && m_aiController->init(sceneSystem);
    inited = inited && m_plController->init(sceneSystem, inputSubsystem);

    m_controllers.push_back(m_aiController);
    m_controllers.push_back(m_plController);

    m_current = 0;
    m_giveAP = true;

    return inited;
}

bool ControlGSystem::reg(Actor& actor)
{
    for (size_t i = 0; i < m_controllers.size(); ++i)
    {
        auto controller = m_controllers[i];
        if (controller->possess(actor))
        {
            m_possessed.emplace_back(i, &actor);
            m_registered.insert(actor.getID());
            return true;
        }
    }
    return false;
}

void ControlGSystem::unreg(ActorID id)
{
    m_registered.erase(id);
    for (auto iter = m_possessed.begin(); iter != m_possessed.end(); ++iter)
    {
        if (iter->second->getID() == id)
        {
            m_possessed.erase(iter);
            break;
        }
    }
    for (auto& controller : m_controllers)
    {
        controller->release(id);
    }
}

void ControlGSystem::update()
{
    if (m_possessed.empty()) return;
    if (m_current >= m_possessed.size())
    {
        m_current = 0;
    }
    auto id = m_possessed[m_current].first;
    auto& actor = *m_possessed[m_current].second;
   
    if (m_giveAP)
    {
        auto apComp = actor.getComponent<ActionPtsComponent>();
        if (apComp)
        {
            // FIXME: non-flexible
            apComp->setCurr(1);
        }
        m_giveAP = false;
    }
    if (m_controllers[id]->control(actor))
    {
        m_giveAP = true;
        ++m_current;
    }
}

void ControlGSystem::clean()
{
    m_current = 0;
    m_giveAP = true;
    m_registered.clear();
    m_possessed.clear();
}

ActorID ControlGSystem::getCurrentID()
{
    // FIXME: current ID is not valid due to sheduler
    // need some "control sequence ended" event from sheduler to continue
    // can implement with unique sequence numbers for cutscene+action+all_dependent
    std::cout << m_possessed.size() << ":" << m_current << std::endl;
    return m_possessed[m_current].first;
}
