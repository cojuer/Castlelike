#include "control_sheduler.h"

#include "ai_controller.h"
#include "player_controller.h"
#include "component__action_pts.h"

bool ControlSheduler::init(InputSubsystem& inputSubsystem, SceneManager& sceneManager, SystemManager& sysManager)
{
    m_aiController = new AIController();
    m_plController = new PlayerController();

    auto inited = true;
    inited = inited && m_aiController->init(sceneManager, sysManager);
    inited = inited && m_plController->init(sceneManager, inputSubsystem, sysManager);

    m_controllers.push_back(m_aiController);
    m_controllers.push_back(m_plController);

    m_sysManager = &sysManager;
    m_current = 0;
    m_giveAP = true;

    return inited;
}

bool ControlSheduler::reg(Actor& actor)
{
    for (size_t i = 0; i < m_controllers.size(); ++i)
    {
        auto controller = m_controllers[i];
        if (controller->possess(actor))
        {
            m_possessed.push_back(std::make_pair(i, &actor));
            m_registered.insert(actor.getID());
            return true;
        }
    }
    return false;
}

void ControlSheduler::unreg(ActorID id)
{
    m_registered.erase(id);
    for (auto iter = m_possessed.begin(); iter != m_possessed.end(); ++iter)
    {
        if (iter->second->getID() == id)
        {
            m_possessed.erase(iter);
            return;
        }
    }
}

void ControlSheduler::update()
{
    if (m_possessed.size() == 0) return;
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

ActorID ControlSheduler::getCurrentID()
{
    // FIXME: current ID is not valid due to sheduler
    // need some "control sequence ended" event from sheduler to continue
    // can implement with unique sequence numbers for cutscene+action+all_dependent
    std::cout << m_possessed.size() << ":" << m_current << std::endl;
    return m_possessed[m_current].first;
}
