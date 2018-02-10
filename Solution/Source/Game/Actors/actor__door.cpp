#include "actor__door.h"

#include "component__graphics.h"
#include "component__reactor__door.h"

Door::Door(ActorID id, Coord pos, const std::string& resID, bool collisive) :
	Actor(id, resID, "none", pos, collisive)
{
	addComponent<ReactorComponentInterface>(*new DoorReactorComponent());
	addComponent<GraphicsInterfaceComponent>(*new GraphicsComponent(7, { "door_normal", "door_opened" }));
}