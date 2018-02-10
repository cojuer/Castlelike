#include "condition.h"

#include "actor.h"
#include "components.h"

namespace condition
{

bool always(CondInput&)
{
    return true;
}

bool has_item(CondInput& args)
{
    auto& user = *get<Actor*>(args, "user");
    auto itemID = get<std::string>(args, "item_id");

    auto bagComponent = user.getComponent<BagComponent>();
    if (bagComponent && bagComponent->hasItem(itemID))
    {
        return true;
    }

    auto equipComponent = user.getComponent<EquipmentComponent>();
    if (equipComponent)
    {
    }

    return false;
}

}
