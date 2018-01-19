#include "actor__storage.h"

#include "component__bag.h"
#include "component__graphics.h"

StorageActor::StorageActor(ActorID id, 
                           Coord pos,
                           const std::string& resID,
                           bool collisive,
                           Container& container,
                           bool solid) :
    Actor(id, resID, ActorType::CONTAINER, pos, collisive)
{
    addComponent<BagComponent>(*new BagComponent(container));
    addComponent<GraphicsInterfaceComponent>(*new GraphicsComponent(5, { m_res }));
}

Container& StorageActor::getContainer() const
{
    return getComponent<BagComponent>()->get();
}
